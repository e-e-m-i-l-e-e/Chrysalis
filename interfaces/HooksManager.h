#ifndef CLOEXTENSIONS_HOOKMANAGER_H
#define CLOEXTENSIONS_HOOKMANAGER_H

#include <unordered_map>
#include <regex>
#include <string>

// ─── undef Qt's emit if it was defined before this header ────────────────────
// Qt defines `#define emit` (empty). asmjit (pulled in by polyhook) uses
// `emit` as a member-function identifier. If the macro is still live when
// asmjit is parsed, `Error emit(InstId instId)` becomes `Error (InstId instId)`
// and MSVC fails with "missing ')' before identifier 'instId'".
// We undef here defensively — this header does not depend on Qt and does not
// restore the macro. TUs that need Qt signal/slot syntax should include Qt
// headers after this file.
#ifdef emit
#  undef emit
#endif
#include <polyhook2/Detour/x64Detour.hpp>

// ─── Logger — optional ────────────────────────────────────────────────────────
// HooksManager emits log output only when the consuming target also links the
// Logger INTERFACE target. Logger propagates the LOGS_DIR compile definition
// via CMake transitive dependencies, so its presence is a reliable signal that
// Logger.h is available and fully configured.
//
// When LOGS_DIR is not defined, HooksManager compiles with zero dependency on
// spdlog or Logger. Each logging call is wrapped in #ifdef LOGS_DIR so the
// lines are absent entirely from the translation unit — no stubs, no overhead.
#ifdef LOGS_DIR
#   include <Logger.h>
#endif

// =============================================================================
//  HookHandle
//  Must be defined before hook_detail so the Before/After std::function
//  signatures that reference it can be fully formed.
//
//  Returned to the caller when registering a before/after callback.
//  Calling remove() schedules the callback for deletion on the next hook
//  invocation — deletion is deferred so it is safe to call remove() from
//  inside the callback itself without invalidating the iterator mid-loop.
// =============================================================================
class HookHandle {
    friend class HooksManager;

    // Raw pointer is intentional: the list is an instance member of HookBase
    // and outlives every HookHandle created during a single hook invocation.
    std::list<std::function<void()> > *_executeLater;
    std::function<void()> _remover;

    HookHandle(std::list<std::function<void()> > &executeLater,
               std::function<void()> remover)
        : _executeLater(&executeLater), _remover(std::move(remover)) {}

public:
    // Schedule this callback for removal. Safe to call from inside the callback.
    void remove() const {
        _executeLater->push_back(_remover);
    }
};

// =============================================================================
//  hook_detail — type-level traits for concepts
//
//  MSVC cannot deduce partial specializations of templates whose non-type
//  template parameter is a member function pointer (e.g. Traits<&Foo::bar>).
//  The workaround is to specialize on the pointer *type* via decltype(F),
//  which uses ordinary type-level partial specialization that all compilers
//  handle reliably.
//
//  These are kept in a detail namespace to avoid polluting global scope.
// =============================================================================
namespace hook_detail {
    // ── AfterType<R, ExtraArgs...> ────────────────────────────────────────────────
    // Lazily builds the After std::function signature.
    // std::conditional_t is NOT used here because it instantiates both branches
    // eagerly — forming std::function<void(HookHandle, void&, ...)> is ill-formed.
    // Partial specialization on void avoids that instantiation entirely.
    template<typename R, typename... ExtraArgs>
    struct AfterType {
        // Non-void: callback receives the return value as a mutable ref first.
        using type = std::function<void(HookHandle, R &, ExtraArgs &...)>;
    };

    template<typename... ExtraArgs>
    struct AfterType<void, ExtraArgs...> {
        // Void: no return value parameter.
        using type = std::function<void(HookHandle, ExtraArgs &...)>;
    };

    template<typename R, typename... ExtraArgs>
    struct IgnoreType {
        using type = std::function<void(HookHandle, bool&, R &, ExtraArgs &...)>;
    };

    template<typename... ExtraArgs>
    struct IgnoreType<void, ExtraArgs...> {
        using type = std::function<void(HookHandle, bool&, ExtraArgs &...)>;
    };

    // ── FuncTraits<T> — undefined base (SFINAE / concept failure for bad T) ──────
    template<typename T>
    struct FuncTraits;

    // ── Free function: R(*)(Args...) ──────────────────────────────────────────────
    template<typename R, typename... Args>
    struct FuncTraits<R(*)(Args...)> {
        using Before = std::function<void(HookHandle, Args &...)>;
        using After = AfterType<R, Args...>::type;
        using Ignore = IgnoreType<R, Args...>::type;
    };

    // ── Non-const member function: R(Class::*)(Args...) ──────────────────────────
    template<typename R, typename Class, typename... Args>
    struct FuncTraits<R(Class::*)(Args...)> {
        using Before = std::function<void(HookHandle, Class *&, Args &...)>;
        using After = AfterType<R, Class *, Args...>::type;
        using Ignore = IgnoreType<R, Class *, Args...>::type;
    };

    // ── Const member function: R(Class::*)(Args...) const ────────────────────────
    template<typename R, typename Class, typename... Args>
    struct FuncTraits<R(Class::*)(Args...) const> {
        using Before = std::function<void(HookHandle, const Class *&, Args &...)>;
        using After = AfterType<R, const Class *, Args...>::type;
        using Ignore = IgnoreType<R, const Class *, Args...>::type;
    };
} // namespace hook_detail

// =============================================================================
//  Concepts
// =============================================================================

// ── HookableFunction<F> ───────────────────────────────────────────────────────
// F must be a free function pointer or a (possibly const) member function
// pointer. Implemented via standard type traits to avoid MSVC's partial
// specialization deduction issues with member function pointer NTTPs.
template<auto F>
concept HookableFunction =
        std::is_member_function_pointer_v<decltype(F)> ||
        (std::is_pointer_v<decltype(F)> &&
         std::is_function_v<std::remove_pointer_t<decltype(F)> >);

// ── BeforeCallbackFor<Cb, F> ──────────────────────────────────────────────────
// Cb must be implicitly convertible to the expected Before callback type for F.
// Gives a readable error at the addBefore call site when the signature is wrong.
template<typename Cb, auto F>
concept BeforeCallbackFor =
        HookableFunction<F> &&
        std::convertible_to<Cb, typename hook_detail::FuncTraits<decltype(F)>::Before>;

// ── AfterCallbackFor<Cb, F> ───────────────────────────────────────────────────
// Same as above for After callbacks, which additionally carry the return value
// (if non-void) as a first mutable reference before the call arguments.
template<typename Cb, auto F>
concept AfterCallbackFor =
        HookableFunction<F> &&
        std::convertible_to<Cb, typename hook_detail::FuncTraits<decltype(F)>::After>;

// ── IgnoreCallbackFor<Cb, F> ───────────────────────────────────────────────────
template<typename Cb, auto F>
concept IgnoreCallbackFor =
        HookableFunction<F> &&
        std::convertible_to<Cb, typename hook_detail::FuncTraits<decltype(F)>::Ignore>;

// =============================================================================
//  HooksManager
//  Manages x64 detour hooks on arbitrary free and member functions.
//
//  Usage:
//    HooksManager::addBefore<&QWidget::show>([](HookHandle h, QWidget*& self) {
//        LOG_INFO("QWidget::show called on {}", self->objectName());
//    });
// =============================================================================
class HooksManager {
    inline static std::string LOGGER_NAME_ = "Hooks Manager";
    // ── AbstractHook ──────────────────────────────────────────────────────────
    // Base class stored in the hooks map. Owns the PLH detour lifetime.
    //
    // IMPORTANT: hook() is NOT called in the constructor. Subclasses must call
    // install() explicitly after all instance state (_instance, _address) is
    // fully initialized. This prevents a race where the hooked function fires
    // between _detour.hook() and the assignment of _instance.
    class AbstractHook {
    public:
        explicit AbstractHook(const uint64_t function, const uint64_t hook, uint64_t *original)
            : _detour(function, hook, original) {}

        // Activate the detour. Must be called after _instance is set.
        void install() {
            _detour.hook();
        }

        virtual ~AbstractHook() {
            _detour.unHook();
        }

    protected:
        PLH::x64Detour _detour;
    };

    // ── HookTraits forward declaration ────────────────────────────────────────
    // Specialised below for free functions and member functions.
    template<auto Function>
    struct HookTraits;

    // =========================================================================
    //  HookBase<R, Original, CallArgs...>
    //
    //  All callback data lives in a heap-allocated instance created when the
    //  first callback is registered and destroyed when the last is removed.
    //  This ensures no static storage lingers after a hook is torn down.
    //
    //  Only two members remain static:
    //    original  — the trampoline pointer filled in by polyhook
    //    _instance — the bridge between the static hook() entry point and the
    //                live instance; set by Hook<> on creation, nulled on deletion
    //
    //  @tparam R         Return type of the hooked function
    //  @tparam Original  Type of the trampoline (original function pointer)
    //  @tparam CallArgs  Full argument list (first arg is Class* for members)
    // =========================================================================
    template<typename R, typename Original, typename... CallArgs>
    struct HookBase {
        // ── Callback types ────────────────────────────────────────────────────
        // Before callbacks receive all call arguments by reference so they can
        // inspect or modify them before the original function runs.
        using Before = std::function<void(HookHandle, CallArgs &...)>;

        // After callbacks additionally receive the return value (if non-void)
        // so they can inspect or replace it. AfterType is used instead of
        // std::conditional_t to avoid eagerly instantiating void& (ill-formed).
        using After = hook_detail::AfterType<R, CallArgs...>::type;

        using Ignore = hook_detail::IgnoreType<R, CallArgs...>::type;

        // ── Instance data — allocated on first use, freed on last removal ─────
        std::list<Before> _before;
        std::list<After> _after;
        std::list<Ignore> _ignore;
        std::list<std::function<void()> > _executeLater;
        void* _address = nullptr;

        void addBefore(Before cb) {
            _before.push_back(std::move(cb));
        }
        void addAfter(After cb) {
            _after.push_back(std::move(cb));
        }
        void addIgnore(Ignore cb) {
            _ignore.push_back(std::move(cb));
        }

        // ── iterate ───────────────────────────────────────────────────────────
        // Walks `list` and invokes each callback with a HookHandle that, when
        // remove() is called, schedules erasure via _executeLater.
        // std::list is used deliberately: erasing by iterator is O(1) and
        // does not invalidate any other iterators.
        template<typename T, typename... Args>
        void iterate(std::list<T> &list, Args &... args) {
            for (auto it = list.begin(); it != list.end(); ++it) {
                (*it)(HookHandle(_executeLater, [this, &list, it] {
#ifdef LOGS_DIR
                    LOG_DEBUG_TO(HooksManager::LOGGER_NAME_, "Removing callback for hook: {}", getName(_address));
#endif
                    list.erase(it);

                    // If no callbacks remain, tear down the detour entirely
                    // to avoid unnecessary overhead on every call.
                    if (_before.empty() && _after.empty() && _ignore.empty()) {
#ifdef LOGS_DIR
                        LOG_DEBUG_TO(HooksManager::LOGGER_NAME_, "No callbacks left — detaching hook: {}", getName(_address));
#endif
                        remove(_address);
                    }
                }), args...);
            }
        }

        // ── hook ──────────────────────────────────────────────────────────────
        // Static entry point installed as the detour target — polyhook requires
        // a plain function pointer, so this cannot be a member function.
        // It accesses all data through _instance, which is guaranteed non-null
        // on entry (install() is only called after _instance is set).
        //
        // _executeLater is swapped into a local list before iteration.
        // This is critical: a deferred removal may call remove(_address) which
        // deletes the HookBase instance — destroying _executeLater while we
        // would still be iterating it. Owning the list on the stack avoids
        // the use-after-free entirely.
        //
        // After flushing deferred removals, _instance is re-checked: if the
        // last callback was removed, the instance is gone, and we call through
        // to the original function without touching any instance state.
        static R hook(CallArgs... args) {
            // Swap pending removals onto the stack before running any of them.
            std::list<std::function<void()> > pending;
            std::swap(_instance->_executeLater, pending);
            for (auto &f: pending) f();

            auto *inst = _instance;
            inst->iterate(inst->_before, args...);

            bool ignore = false;
            if constexpr (std::is_void_v<R>) {
                inst->iterate(inst->_ignore, ignore, args...);
                if (!ignore) original(args...);
                if (_instance) inst->iterate(inst->_after, args...);
            } else {
                R result;
                inst->iterate(inst->_ignore, ignore, result, args...);
                if (!ignore) result = original(args...);
                if (_instance) inst->iterate(inst->_after, result, args...);
                return result;
            }
        }

        // ── Static members ────────────────────────────────────────────────────
        // Trampoline to the original function, filled in by polyhook.
        static inline Original original = nullptr;

        // Bridge from the static hook() entry point to the live instance.
        // Owning pointer: Hook<Target> creates and destroys it.
        static inline HookBase *_instance = nullptr;
    };

    // =========================================================================
    //  HookBaseOutPtr<R, Original, Class, Args...>
    //
    //  Variant of HookBase used when R is NOT trivially copyable.
    //  Under the MSVC x64 ABI the compiler inserts a hidden second argument
    //  after `this` that points to the caller-allocated return buffer:
    //
    //    void hook(const Class* self, R* ret, Args... args)
    //
    //  This means `original` has type void(*)(const Class*, R*, Args...) and
    //  the detour entry point must match that exact signature.
    //
    //  User-facing Before/After/Ignore signatures are identical to HookBase —
    //  the hidden R* buffer is transparent to callers. Before receives (self,
    //  args...), After receives (R&, self, args...) where R& is dereferenced
    //  from *ret after the original (or ignore path) has populated it.
    //
    //  Ignore note: when a callback sets ignore=true it must also populate the
    //  R& it receives. R is default-constructed before Ignore iteration; for
    //  all non-trivially-copyable Qt types (QVariant, QString, …) this is safe.
    //
    //  @tparam R        Return type (must satisfy !std::is_trivially_copyable_v<R>)
    //  @tparam Original Trampoline type: void(*)(const Class*, R*, Args...)
    //  @tparam Class    Class that owns the hooked function (without const/ptr)
    //  @tparam Args     Argument types (excluding this and the hidden R* buffer)
    // =========================================================================
    template<typename R, typename Original, typename Class, typename... Args>
    struct HookBaseOutPtr {
        // ── Callback types ────────────────────────────────────────────────────
        // Identical to HookBase equivalents for a const member — the hidden R*
        // buffer never surfaces in the user-facing signatures.
        using Before = std::function<void(HookHandle, const Class *&, Args &...)>;
        using After  = hook_detail::AfterType<R, const Class *, Args...>::type;
        using Ignore = hook_detail::IgnoreType<R, const Class *, Args...>::type;

        // ── Instance data ─────────────────────────────────────────────────────
        std::list<Before> _before;
        std::list<After>  _after;
        std::list<Ignore> _ignore;
        std::list<std::function<void()>> _executeLater;
        void *_address = nullptr;

        void addBefore(Before cb) { _before.push_back(std::move(cb)); }
        void addAfter (After  cb) { _after .push_back(std::move(cb)); }
        void addIgnore(Ignore cb) { _ignore.push_back(std::move(cb)); }

        template<typename T, typename... A>
        void iterate(std::list<T> &list, A &... args) {
            for (auto it = list.begin(); it != list.end(); ++it) {
                (*it)(HookHandle(_executeLater, [this, &list, it] {
#ifdef LOGS_DIR
                    LOG_DEBUG_TO(HooksManager::LOGGER_NAME_, "Removing callback for hook: {}", getName(_address));
#endif
                    list.erase(it);
                    if (_before.empty() && _after.empty() && _ignore.empty()) {
#ifdef LOGS_DIR
                        LOG_DEBUG_TO(HooksManager::LOGGER_NAME_, "No callbacks left — detaching hook: {}", getName(_address));
#endif
                        remove(_address);
                    }
                }), args...);
            }
        }

        // ── hook ──────────────────────────────────────────────────────────────
        // ABI-matching detour entry point. Returns void; `ret` is the
        // caller-allocated return buffer that MSVC passes as the second
        // argument for non-trivially-copyable return types.
        //
        // _executeLater safety and _instance null-check mirror HookBase::hook
        // exactly — see comments there for the rationale.
        static void hook(const Class *self, R *ret, Args... args) {
            std::list<std::function<void()>> pending;
            std::swap(_instance->_executeLater, pending);
            for (auto &f : pending) f();

            auto *inst = _instance;

            // Before — self is a local copy; callbacks can redirect the pointer.
            inst->iterate(inst->_before, self, args...);

            // Ignore — R is default-constructed so the callback can populate it
            // when choosing to skip the original call.
            bool ignore = false;
            R result{};
            inst->iterate(inst->_ignore, ignore, result, self, args...);

            if (!ignore) {
                original(self, ret, args...);   // original writes into *ret
            } else if (ret) {
                *ret = std::move(result);        // user-supplied value → caller's buffer
            }

            // After — expose the final committed value through *ret by reference.
            if (_instance && ret)
                inst->iterate(inst->_after, *ret, self, args...);
        }

        // ── Static members ────────────────────────────────────────────────────
        static inline Original      original  = nullptr;
        static inline HookBaseOutPtr *_instance = nullptr;
    };

    // ── Hook<Target> ──────────────────────────────────────────────────────────
    // Concrete hook stored in the map. Bridges the type-erased AbstractHook
    // with the typed HookTraits so addBefore/addAfter remain type-safe.
    //
    // Owns the HookBase instance: creates it in the constructor, deletes it
    // (and clears _instance) in the destructor. After destruction, all callback
    // lists and associated memory are freed.
    //
    // Note: template constraint uses `requires` clause — MSVC C7600 rejects
    // the shorthand `template<HookableFunction auto Target>` for non-type params.
    template<auto Target> requires HookableFunction<Target>
    struct Hook : AbstractHook {
        explicit Hook(void *address)
            : AbstractHook(
                HookTraits<Target>::address(),
                reinterpret_cast<uint64_t>(&HookTraits<Target>::hook),
                reinterpret_cast<uint64_t *>(&HookTraits<Target>::original)) {
            // Allocate and wire up the instance BEFORE installing the detour.
            // If install() came first, the hooked function could fire between
            // _detour.hook() and the _instance assignment, hitting a null pointer.
            auto *inst = new HookTraits<Target>();
            inst->_address = address;
            HookTraits<Target>::_instance = inst;

            install(); // detour goes live only now — _instance is guaranteed valid
        }

        ~Hook() override {
            // AbstractHook's destructor calls unHook() first, guaranteeing the
            // detour is removed before we free the instance. No in-flight hook()
            // call can be using _instance after unHook() returns.
            //
            // Cast to the concrete type so the correct destructor is called
            // without requiring a virtual destructor on HookBase.
            delete static_cast<HookTraits<Target> *>(HookTraits<Target>::_instance);
            HookTraits<Target>::_instance = nullptr;
        }

        void addBefore(HookTraits<Target>::Before cb) {
            HookTraits<Target>::_instance->addBefore(std::move(cb));
        }

        void addAfter(HookTraits<Target>::After cb) {
            HookTraits<Target>::_instance->addAfter(std::move(cb));
        }

        void addIgnore(HookTraits<Target>::Ignore cb) {
            HookTraits<Target>::_instance->addIgnore(std::move(cb));
        }
    };

    // =========================================================================
    //  HookTraits — free function specialization
    //  @tparam R        Return type
    //  @tparam Args     Argument types
    //  @tparam Function Pointer to the free function to hook
    // =========================================================================
    template<typename R, typename... Args, R(*Function)(Args...)>
    struct HookTraits<Function> : HookBase<R, R(*)(Args...), Args...> {
        static uint64_t address() {
            return reinterpret_cast<uint64_t>(Function);
        }
    };

    // =========================================================================
    //  HookTraits — non-const member function specialization
    //  @tparam R        Return type
    //  @tparam Class    Class that owns the member function
    //  @tparam Args     Argument types (excluding implicit this)
    //  @tparam Function Pointer to the member function to hook
    // =========================================================================
    template<typename R, typename Class, typename... Args, R(Class::*Function)(Args...)>
    struct HookTraits<Function> : HookBase<R, R(*)(Class *, Args...), Class *, Args...> {
        static uint64_t address() {
            // Reinterpret a member function pointer as a raw address.
            // A union is used because member pointers cannot be cast via
            // reinterpret_cast directly — this is the standard workaround
            // on MSVC/GCC/Clang for x64 single-inheritance vtable layouts.
            union {
                R (Class::*mfp)(Args...);
                uint64_t addr;
            } u;
            u.mfp = Function;
            return u.addr;
        }
    };

    // =========================================================================
    //  ConstMemberHookBase — ABI-aware base selector for const member hooks
    //
    //  Trivially-copyable R (int, float, small POD…):
    //    MSVC returns the value in a register → normal HookBase with R return.
    //
    //  Non-trivially-copyable R (QVariant, QString, QColor…):
    //    MSVC inserts a hidden R* as the second argument and the function
    //    returns void → HookBaseOutPtr with void(*)(const Class*, R*, Args...).
    //
    //  Both branches expose identical Before/After/Ignore callback signatures
    //  to callers, so the ABI difference is completely transparent at the
    //  addBefore / addAfter / addIgnore call sites.
    // =========================================================================
    template<typename R, typename Class, typename... Args>
    using ConstMemberHookBase = std::conditional_t<
        std::is_trivially_copyable_v<R>,
        HookBase    <R, R(*)(const Class *, Args...),           const Class *, Args...>,
        HookBaseOutPtr<R, void(*)(const Class *, R *, Args...), Class,         Args...>
    >;

    // =========================================================================
    //  HookTraits — const member function specialization
    //  Mirrors the non-const variant above. The implicit `this` pointer becomes
    //  `const Class*` throughout: in the trampoline signature, and in the
    //  lambda parameter list seen by callers.
    //
    //  The base class is selected by ConstMemberHookBase:
    //    • trivially-copyable R  → HookBase       (register return)
    //    • non-trivially-copyable R → HookBaseOutPtr (hidden out-ptr ABI)
    //
    //  Without this specialization any addBefore<&Foo::constMethod> call
    //  silently falls through to the undefined primary template and fails to
    //  compile. Examples: QSettings::value, QSettings::contains, QVariant::toString.
    // =========================================================================
    template<typename R, typename Class, typename... Args, R(Class::*Function)(Args...) const>
    struct HookTraits<Function> : ConstMemberHookBase<R, Class, Args...> {
        static uint64_t address() {
            union {
                R (Class::*mfp)(Args...) const;
                uint64_t addr;
            } u;
            u.mfp = Function;
            return u.addr;
        }
    };

    // ── getHook ───────────────────────────────────────────────────────────────
    // Returns the existing Hook for F, or creates and registers a new one.
    template<auto F> requires HookableFunction<F>
    static Hook<F> *getHook() {
        // Extract the opaque address from the function pointer.
        union {
            decltype(F) p;
            void *addr;
        } u;
        u.p = F;

        const auto it = _hooks.find(u.addr);
        if (it == _hooks.end()) {
            auto *hook = new Hook<F>(u.addr);
            _hooks[u.addr] = hook;
#ifdef LOGS_DIR
            LOG_INFO_TO(HooksManager::LOGGER_NAME_, "Hook created: {}", getName(u.addr));
#endif
            return hook;
        }

        return dynamic_cast<Hook<F>*>(it->second);
    }

    // ── remove ────────────────────────────────────────────────────────────────
    // Unregisters and destroys the Hook for `address`. The Hook destructor
    // unregisters the detour and deletes the HookBase instance, freeing all
    // callback lists. Called automatically when the last callback is removed.
    static void remove(void* address) {
        const auto it = _hooks.find(address);
        if (it == _hooks.end()) return;
        const auto *hook = it->second;
        _hooks.erase(it);
        delete hook; // ~Hook() → unHook() then ~HookBase()
    }

    // ── getName ───────────────────────────────────────────────────────────────
    // Extracts a human-readable "Class::method" label from the RTTI type name
    // of the hook stored at `address`.
    static std::string getName(void* address) {
        const auto it = _hooks.find(address);
        if (it == _hooks.end()) return "<unknown>";

        std::string raw = typeid(*it->second).name();

        // The template instantiation string contains the original function
        // signature — extract the last "Namespace::Method(" token from it.
        static const std::regex re(R"(<[^>]*?(\w+::\w+)\()");
        std::smatch match;
        if (std::regex_search(raw, match, re) && match.size() > 1)
            return match[1].str();
        return raw;
    }

    // ── _hooks ────────────────────────────────────────────────────────────────
    // Global map from opaque function address to its live AbstractHook.
    // std::unordered_map gives O(1) average lookup.
    static inline std::unordered_map<void*, AbstractHook*> _hooks;

public:
    // ── addBefore ─────────────────────────────────────────────────────────────
    // Register a callback to run before function F.
    // Creates the hook automatically on first registration.
    //
    // Compile-time guarantees:
    //   • F must be a free or member function pointer          (HookableFunction)
    //   • Callback signature must match (HookHandle, Args&...) (BeforeCallbackFor)
    template<auto F, typename Callback> requires BeforeCallbackFor<Callback, F>
    static void addBefore(Callback &&callback) {
        getHook<F>()->addBefore(std::forward<Callback>(callback));
    }

    // ── addAfter ──────────────────────────────────────────────────────────────
    // Register a callback to run after function F.
    // Creates the hook automatically on first registration.
    //
    // Compile-time guarantees:
    //   • F must be a free or member function pointer                (HookableFunction)
    //   • Callback signature must match (HookHandle[, R&], Args&...) (AfterCallbackFor)
    template<auto F, typename Callback> requires AfterCallbackFor<Callback, F>
    static void addAfter(Callback &&callback) {
        getHook<F>()->addAfter(std::forward<Callback>(callback));
    }

    template<auto F, typename Callback> requires IgnoreCallbackFor<Callback, F>
    static void addIgnore(Callback &&callback) {
        getHook<F>()->addIgnore(std::forward<Callback>(callback));
    }
};

#endif // CLOEXTENSIONS_HOOKMANAGER_H