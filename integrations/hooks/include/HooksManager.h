#ifndef CHRYSALIS_HOOKMANAGER_H
#define CHRYSALIS_HOOKMANAGER_H

#include <list>
#include <regex>
#include <string>
#include <optional>

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

#include "types.h"
#include "Logging.h"
#include "BaseHook.h"
#include "HookHandle.h"
#include "HooksLibraryExport.h"

// =============================================================================
//  HooksManager
//  Manages x64 detour hooks on arbitrary free and member functions.
//
//  Usage:
//    HooksManager::addBefore<&QWidget::show>([](HookHandle h, QWidget*& self) {
//        LOG_INFO("QWidget::show called on {}", self->objectName());
//    });
// =============================================================================
class HOOKS HooksManager {
    static constexpr auto LOGGER_NAME_ = "Hooks Manager";
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
        using After = AfterType<R, CallArgs...>::type;

        // Replace callbacks fully substitute for the original call: they get
        // the (mutable) call arguments and must produce the return value.
        using Replace = ReplaceType<R, CallArgs...>::type;

        // IgnoreConditionally callbacks decide, per call, whether the original
        // should run — like Before, plus a leading bool& the callback sets.
        using IgnoreConditionally = IgnoreConditionallyType<R, CallArgs...>::type;

        // ── Instance data — allocated on first use, freed on last removal ─────
        std::list<Before> _before;
        std::list<After> _after;
        std::optional<Replace> _replace;                 // only one Replace per function
        std::optional<IgnoreConditionally> _ignoreConditionally; // only one per function
        bool _ignoreActive = false;                       // only one Ignore per function (void only)
        std::list<std::function<void()> > _executeLater;
        void* _address = nullptr;

        void addBefore(Before cb, std::optional<size_t> position = std::nullopt) {
            insertAt(_before, std::move(cb), position);
        }
        void addAfter(After cb, std::optional<size_t> position = std::nullopt) {
            insertAt(_after, std::move(cb), position);
        }
        void removeBeforeAt(size_t position) {
            eraseAt(_before, position);
        }
        void removeAfterAt(size_t position) {
            eraseAt(_after, position);
        }
        void setReplace(Replace cb) {
            _replace = std::move(cb);
        }
        void clearReplace() {
            _replace.reset();
        }
        void setIgnoreConditionally(IgnoreConditionally cb) {
            _ignoreConditionally = std::move(cb);
        }
        void clearIgnoreConditionally() {
            _ignoreConditionally.reset();
        }

        // True once no Before/After/Replace/Ignore/IgnoreConditionally
        // registration remains — the signal that the detour can be torn down.
        bool isEmpty() const {
            return _before.empty() && _after.empty() && !_replace.has_value()
                   && !_ignoreActive && !_ignoreConditionally.has_value();
        }

        // ── iterate ───────────────────────────────────────────────────────────
        // Walks `list` and invokes each callback with a HookHandle that, when
        // remove() is called, schedules erasure via _executeLater. Erasure
        // itself only happens later, when a flush loop runs the queued
        // closure (see hook()'s tail) — never synchronously from here, since
        // that could invalidate the very list this loop is iterating.
        // std::list is used deliberately: erasing by iterator is O(1) and
        // does not invalidate any other iterators.
        template<typename T, typename... Args>
        void iterate(std::list<T> &list, Args &... args) {
            for (auto it = list.begin(); it != list.end(); ++it) {
                (*it)(HookHandle(_executeLater, [this, &list, it] {
                    LOG_DEBUG_TO(LOGGER_NAME_, "Removing callback for hook: {}", getName(_address));
                    list.erase(it);
                }), args...);
            }
        }

        // ── hook ──────────────────────────────────────────────────────────────
        // Static entry point installed as the detour target — polyhook requires
        // a plain function pointer, so this cannot be a member function.
        // It accesses all data through _instance, which is guaranteed non-null
        // on entry (install() is only called after _instance is set).
        //
        // Deferred removals (from handle.remove(), called by any Before/
        // Replace/IgnoreConditionally/After callback in THIS call) are
        // flushed at the very end — after Before, Replace/Ignore, and After
        // have all run — rather than at entry. This is the one safe moment
        // to also tear the detour down if that flush left nothing registered:
        // nothing after this point touches `inst` or the trampoline again, so
        // unHook() invalidating them is harmless. Doing this any earlier (or
        // synchronously mid-iteration) risks calling through an already-
        // unhooked/freed trampoline later in the same call — this is exactly
        // what caused a real crash during development; see git history/PR
        // discussion for HooksManagerTest's *_RemoveViaHandle tests.
        //
        // Replace takes priority over the original call when set (it fully
        // substitutes for it). Ignore (void functions only) simply skips the
        // call. Both are mutually exclusive in practice, but if a user sets
        // both, Replace wins since it is the more explicit instruction.
        static R hook(CallArgs... args) {
            auto *inst = _instance;
            inst->iterate(inst->_before, args...);

            auto replaceHandle = [inst] {
                return HookHandle(inst->_executeLater, [inst] {
                    inst->_replace.reset();
                });
            };
            auto ignoreCondHandle = [inst] {
                return HookHandle(inst->_executeLater, [inst] {
                    inst->_ignoreConditionally.reset();
                });
            };

            if constexpr (std::is_void_v<R>) {
                if (inst->_replace) {
                    (*inst->_replace)(replaceHandle(), args...);
                } else {
                    bool ignore = inst->_ignoreActive;
                    if (inst->_ignoreConditionally) {
                        (*inst->_ignoreConditionally)(ignoreCondHandle(), ignore, args...);
                    }
                    if (!ignore) original(args...);
                }
                inst->iterate(inst->_after, args...);
                finalize(inst);
            } else if constexpr (std::is_reference_v<R>) {
                // Reference return: a reference variable cannot be
                // default-initialized, so use a pointer for result storage.
                std::remove_reference_t<R>* result_ptr = nullptr;
                if (inst->_replace) {
                    result_ptr = &(*inst->_replace)(replaceHandle(), args...);
                } else {
                    bool ignore = inst->_ignoreActive;
                    if (inst->_ignoreConditionally) {
                        (*inst->_ignoreConditionally)(ignoreCondHandle(), ignore, result_ptr, args...);
                    }
                    if (!ignore) result_ptr = &original(args...);
                }
                if (result_ptr) inst->iterate(inst->_after, *result_ptr, args...);
                finalize(inst);
                return *result_ptr; // NOLINT: caller must ensure result_ptr is non-null
            } else {
                R result{};
                if (inst->_replace) {
                    result = (*inst->_replace)(replaceHandle(), args...);
                } else {
                    bool ignore = inst->_ignoreActive;
                    if (inst->_ignoreConditionally) {
                        (*inst->_ignoreConditionally)(ignoreCondHandle(), ignore, result, args...);
                    }
                    if (!ignore) result = original(args...);
                }
                inst->iterate(inst->_after, result, args...);
                finalize(inst);
                return result;
            }
        }

        // ── finalize ──────────────────────────────────────────────────────────
        // Shared tail for every hook() variant in this file (this one and the
        // four hand-rolled hidden-pointer ones below): flush deferred
        // removals now that every callback for this call has had its chance
        // to self-remove, then tear the detour down if nothing is left
        // registered. Must be the LAST thing done with `inst` in the calling
        // hook() — see hook()'s comment above for why the timing matters.
        static void finalize(HookBase *inst) {
            std::list<std::function<void()> > pending;
            std::swap(inst->_executeLater, pending);
            for (auto &f: pending) f();
            if (inst->isEmpty()) remove(inst->_address);
        }

        // ── Static members ────────────────────────────────────────────────────
        // Trampoline to the original function, filled in by polyhook.
        static inline Original original = nullptr;

        // Bridge from the static hook() entry point to the live instance.
        // Owning pointer: Hook<Target> creates and destroys it.
        static inline HookBase *_instance = nullptr;
    };

    // ── HookTraits forward declaration ────────────────────────────────────────
    // Specialised below for free functions and member functions.
    template<auto Function>
    struct HookTraits;
    // ── Hook<Target> ──────────────────────────────────────────────────────────
    // Concrete hook stored in the map. Bridges the type-erased BaseHook
    // with the typed HookTraits so addBefore/addAfter/addReplace/addIgnore
    // remain type-safe.
    //
    // Owns the HookBase instance: creates it in the constructor, deletes it
    // (and clears _instance) in the destructor. After destruction, all callback
    // lists and associated memory are freed.
    //
    // Note: template constraint uses `requires` clause — MSVC C7600 rejects
    // the shorthand `template<HookableFunction auto Target>` for non-type params.
    template<auto Target> requires HookableFunction<Target>
    struct Hook : BaseHook {
        explicit Hook(void *address)
            : BaseHook(
                HookTraits<Target>::address(),
                reinterpret_cast<uint64_t>(&HookTraits<Target>::hook),
                reinterpret_cast<uint64_t *>(&HookTraits<Target>::original)) {
            // Allocate and wire up the instance BEFORE installing the detour.
            // If install() came first, the hooked function could fire between
            // _detour.hook() and the _instance assignment, hitting a null pointer.
            auto *inst = new HookTraits<Target>();
            inst->_address = address;
            HookTraits<Target>::_instance = inst;

            if (!install()) {
                // Roll back: the detour never took effect (see install()'s
                // comment for why), so the instance/address are pointing at
                // an inert registration nothing will ever call into. Leaving
                // it in place would make every addBefore/addAfter/etc. call
                // silently do nothing forever — fail loudly instead so the
                // caller finds out immediately, at the call site, rather
                // than debugging "why doesn't my hook fire".
                delete inst;
                HookTraits<Target>::_instance = nullptr;
                throw std::runtime_error(
                    "HooksManager: failed to install detour — target function's "
                    "compiled prologue is too short to hook (this can happen with "
                    "trivial one-line functions under aggressive optimization)");
            }
        }

        ~Hook() override {
            // BaseHook's destructor calls unHook() first, guaranteeing the
            // detour is removed before we free the instance. No in-flight hook()
            // call can be using _instance after unHook() returns.
            //
            // Cast to the concrete type so the correct destructor is called
            // without requiring a virtual destructor on HookBase.
            delete static_cast<HookTraits<Target> *>(HookTraits<Target>::_instance);
            HookTraits<Target>::_instance = nullptr;
        }

        void addBefore(HookTraits<Target>::Before cb, std::optional<size_t> position = std::nullopt) {
            HookTraits<Target>::_instance->addBefore(std::move(cb), position);
        }

        void addAfter(HookTraits<Target>::After cb, std::optional<size_t> position = std::nullopt) {
            HookTraits<Target>::_instance->addAfter(std::move(cb), position);
        }

        void removeBeforeAt(size_t position) {
            HookTraits<Target>::_instance->removeBeforeAt(position);
        }

        void removeAfterAt(size_t position) {
            HookTraits<Target>::_instance->removeAfterAt(position);
        }

        void setReplace(HookTraits<Target>::Replace cb) {
            HookTraits<Target>::_instance->setReplace(std::move(cb));
        }

        void clearReplace() {
            HookTraits<Target>::_instance->clearReplace();
        }

        void setIgnoreConditionally(HookTraits<Target>::IgnoreConditionally cb) {
            HookTraits<Target>::_instance->setIgnoreConditionally(std::move(cb));
        }

        void clearIgnoreConditionally() {
            HookTraits<Target>::_instance->clearIgnoreConditionally();
        }

        void setIgnoreActive(bool active) {
            HookTraits<Target>::_instance->_ignoreActive = active;
        }

        bool empty() const {
            return HookTraits<Target>::_instance->isEmpty();
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
    //
    //  Handles trivial and void R (no hidden return pointer involved — the
    //  compiler returns the value in a register either way, whether R is
    //  declared here as a real by-value return or the real member function's
    //  own return; both compile identically). Non-trivial, non-void R needs
    //  its own specialization below — see the comment there for why.
    // =========================================================================
    template<typename R, typename Class, typename... Args, R(Class::*Function)(Args...)>
    requires (std::is_trivial_v<R> || std::is_void_v<R>)
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
    //  HookTraits — non-const member function, NON-TRIVIAL non-void return
    //
    //  Why this needs its own specialization instead of just declaring
    //  hook()/original with plain by-value return type R (as the trivial/void
    //  branch above does): R being non-trivial means the real, compiled
    //  Class::Function *itself* uses a hidden caller-allocated return pointer
    //  under the hood — but WHERE that pointer sits in the parameter list is
    //  a property of the *member function* calling convention specifically:
    //    • MSVC x64:    this, hidden-return-pointer, then explicit args
    //    • Itanium ABI: hidden-return-pointer, this, then explicit args
    //  hook()/original, as declared here, are ordinary *free* functions that
    //  happen to take an explicit Class* parameter to model `this` — the
    //  compiler has no idea that parameter is meant to be `this`, so it
    //  applies the *free function* rule when deciding where to insert a
    //  hidden pointer (strictly first, before every explicit parameter,
    //  including the one modeling `this`) — which disagrees with where the
    //  real member function actually put it. Trivial/void R never triggers
    //  this because there's no hidden pointer to place either way, so both
    //  rules coincide and the plain by-value branch above works unmodified.
    //
    //  The fix: declare the hidden pointer *explicitly*, by hand, in the
    //  platform-correct position, rather than relying on the compiler to
    //  insert one implicitly for a by-value R return. CallArgs (used to
    //  derive Before/After/Replace/IgnoreConditionally) deliberately excludes
    //  the pointer — those callback types stay the same plain-R-by-value
    //  shape used everywhere else in this file; only the low-level
    //  hook()/original signatures need to know about it.
    // =========================================================================
#if defined(_MSC_VER)
    template<typename R, typename Class, typename... Args, R(Class::*Function)(Args...)>
    requires (!std::is_trivial_v<R> && !std::is_void_v<R>)
    struct HookTraits<Function> : HookBase<R, void(*)(Class *, R *, Args...), Class *, Args...> {
        using Base = HookBase<R, void(*)(Class *, R *, Args...), Class *, Args...>;

        static uint64_t address() {
            union {
                R (Class::*mfp)(Args...);
                uint64_t addr;
            } u;
            u.mfp = Function;
            return u.addr;
        }

        // See the class-level comment above for why this can't just be a
        // plain by-value-returning hook(): `ret` is placed explicitly, by
        // hand, in the position MSVC's x64 ABI actually uses for a member
        // function (this, ret, args...) — it is NOT the compiler-inferred
        // hidden pointer for a by-value return, which would land elsewhere.
        //
        // `*ret` is exactly ONE of: constructed by original() (normal path),
        // or placement-constructed here from a Replace/IgnoreConditionally
        // result (skip path) — never both, never neither.
        static R* hook(Class* thiz, R* ret, Args... args) {

            auto* inst = Base::_instance;
            inst->iterate(inst->_before, thiz, args...);

            if (inst->_replace) {
                new (ret) R((*inst->_replace)(HookHandle(inst->_executeLater, [inst] {
                    inst->_replace.reset();
                }), thiz, args...));
            } else {
                bool ignore = inst->_ignoreActive; // always false here (Ignore is void-only)
                R localResult{};                   // safe placeholder — NOT *ret
                if (inst->_ignoreConditionally) {
                    (*inst->_ignoreConditionally)(HookHandle(inst->_executeLater, [inst] {
                        inst->_ignoreConditionally.reset();
                    }), ignore, localResult, thiz, args...);
                }
                if (!ignore) {
                    Base::original(thiz, ret, args...); // constructs *ret itself
                } else {
                    new (ret) R(std::move(localResult)); // *ret still raw: construct from the substitute
                }
            }

            if (Base::_instance) inst->iterate(inst->_after, *ret, thiz, args...);

            Base::finalize(inst);

            return ret;
        }
    };
#else
    template<typename R, typename Class, typename... Args, R(Class::*Function)(Args...)>
    requires (!std::is_trivial_v<R> && !std::is_void_v<R>)
    struct HookTraits<Function> : HookBase<R, void(*)(R *, Class *, Args...), Class *, Args...> {
        using Base = HookBase<R, void(*)(R *, Class *, Args...), Class *, Args...>;

        static uint64_t address() {
            union {
                R (Class::*mfp)(Args...);
                uint64_t addr;
            } u;
            u.mfp = Function;
            return u.addr;
        }

        // Itanium ABI order: hidden return pointer first, then `this`. See
        // the class-level comment above for the full explanation.
        static R* hook(R* ret, Class* thiz, Args... args) {

            auto* inst = Base::_instance;
            inst->iterate(inst->_before, thiz, args...);

            if (inst->_replace) {
                new (ret) R((*inst->_replace)(HookHandle(inst->_executeLater, [inst] {
                    inst->_replace.reset();
                }), thiz, args...));
            } else {
                bool ignore = inst->_ignoreActive;
                R localResult{};
                if (inst->_ignoreConditionally) {
                    (*inst->_ignoreConditionally)(HookHandle(inst->_executeLater, [inst] {
                        inst->_ignoreConditionally.reset();
                    }), ignore, localResult, thiz, args...);
                }
                if (!ignore) {
                    Base::original(ret, thiz, args...);
                } else {
                    new (ret) R(std::move(localResult));
                }
            }

            if (Base::_instance) inst->iterate(inst->_after, *ret, thiz, args...);

            Base::finalize(inst);

            return ret;
        }
    };
#endif

    // =========================================================================
    //  HookTraits — const member function specialization
    //  Mirrors the non-const variant above, including the trivial/void vs
    //  non-trivial split and why it's needed — see the comment above the
    //  non-const non-trivial specialization for the full explanation. The
    //  implicit `this` pointer becomes `const Class*` throughout.
    //
    //  Without this specialization any addBefore<&Foo::constMethod> call
    //  silently falls through to the undefined primary template and fails to
    //  compile. Examples: QSettings::value, QSettings::contains, QVariant::toString.
    // =========================================================================
    template<typename R, typename Class, typename... Args, R(Class::*Function)(Args...) const>
    requires (std::is_trivial_v<R> || std::is_void_v<R>)
    struct HookTraits<Function> : HookBase<R, R(*)(const Class *, Args...), const Class *, Args...> {
        static uint64_t address() {
            union {
                R (Class::*mfp)(Args...) const;
                uint64_t addr;
            } u;
            u.mfp = Function;
            return u.addr;
        }
    };

#if defined(_MSC_VER)
    template<typename R, typename Class, typename... Args, R(Class::*Function)(Args...) const>
    requires (!std::is_trivial_v<R> && !std::is_void_v<R>)
    struct HookTraits<Function> : HookBase<R, void(*)(const Class *, R *, Args...), const Class *, Args...> {
        using Base = HookBase<R, void(*)(const Class *, R *, Args...), const Class *, Args...>;

        static uint64_t address() {
            union {
                R (Class::*mfp)(Args...) const;
                uint64_t addr;
            } u;
            u.mfp = Function;
            return u.addr;
        }

        static R* hook(const Class* thiz, R* ret, Args... args) {
            auto* inst = Base::_instance;
            inst->iterate(inst->_before, thiz, args...);

            if (inst->_replace) {
                new (ret) R((*inst->_replace)(HookHandle(inst->_executeLater, [inst] {
                    inst->_replace.reset();
                }), thiz, args...));
            } else {
                bool ignore = inst->_ignoreActive;
                R localResult{};
                if (inst->_ignoreConditionally) {
                    (*inst->_ignoreConditionally)(HookHandle(inst->_executeLater, [inst] {
                        inst->_ignoreConditionally.reset();
                    }), ignore, localResult, thiz, args...);
                }
                if (!ignore) {
                    Base::original(thiz, ret, args...);
                } else {
                    new (ret) R(std::move(localResult));
                }
            }

            if (Base::_instance) inst->iterate(inst->_after, *ret, thiz, args...);

            Base::finalize(inst);

            return ret;
        }
    };
#else
    template<typename R, typename Class, typename... Args, R(Class::*Function)(Args...) const>
    requires (!std::is_trivial_v<R> && !std::is_void_v<R>)
    struct HookTraits<Function> : HookBase<R, void(*)(R *, const Class *, Args...), const Class *, Args...> {
        using Base = HookBase<R, void(*)(R *, const Class *, Args...), const Class *, Args...>;

        static uint64_t address() {
            union {
                R (Class::*mfp)(Args...) const;
                uint64_t addr;
            } u;
            u.mfp = Function;
            return u.addr;
        }

        static R* hook(R* ret, const Class* thiz, Args... args) {

            auto* inst = Base::_instance;
            inst->iterate(inst->_before, thiz, args...);

            if (inst->_replace) {
                new (ret) R((*inst->_replace)(HookHandle(inst->_executeLater, [inst] {
                    inst->_replace.reset();
                }), thiz, args...));
            } else {
                bool ignore = inst->_ignoreActive;
                R localResult{};
                if (inst->_ignoreConditionally) {
                    (*inst->_ignoreConditionally)(HookHandle(inst->_executeLater, [inst] {
                        inst->_ignoreConditionally.reset();
                    }), ignore, localResult, thiz, args...);
                }
                if (!ignore) {
                    Base::original(ret, thiz, args...);
                } else {
                    new (ret) R(std::move(localResult));
                }
            }

            if (Base::_instance) inst->iterate(inst->_after, *ret, thiz, args...);

            Base::finalize(inst);

            return ret;
        }
    };
#endif

    // ── list helpers — positional insert/erase ────────────────────────────────
    // Shared by Before/After lists so "insert at any place" / "remove via
    // position" behave identically for both callback kinds.
    template<typename T>
    static void insertAt(std::list<T> &list, T item, std::optional<size_t> position) {
        if (!position || *position >= list.size()) {
            list.push_back(std::move(item));
        } else {
            auto it = list.begin();
            std::advance(it, static_cast<long>(*position));
            list.insert(it, std::move(item));
        }
    }

    template<typename T>
    static void eraseAt(std::list<T> &list, size_t position) {
        if (position >= list.size()) return;
        auto it = list.begin();
        std::advance(it, static_cast<long>(position));
        list.erase(it);
    }
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
            LOG_INFO_TO(LOGGER_NAME_, "Hook has been created: {}", getName(u.addr));
            return hook;
        }

        return dynamic_cast<Hook<F>*>(it->second);
    }

    // ── findHook ──────────────────────────────────────────────────────────────
    // Like getHook, but never creates one. Used by the position/remove-style
    // APIs, which are no-ops on a function that was never hooked.
    template<auto F> requires HookableFunction<F>
    static Hook<F> *findHook() {
        union {
            decltype(F) p;
            void *addr;
        } u;
        u.p = F;

        const auto it = _hooks.find(u.addr);
        if (it == _hooks.end()) return nullptr;
        return dynamic_cast<Hook<F>*>(it->second);
    }

    // ── tearDownIfEmpty ───────────────────────────────────────────────────────
    // After an external (non-handle) removal, detach the detour entirely once
    // no Before/After/Replace/Ignore registration remains — same policy as
    // the deferred, handle-based removal path in HookBase::finalize(), which
    // runs this same check at the end of every hook() call.
    template<auto F>
    static void tearDownIfEmpty(Hook<F> *hook) {
        if (hook->empty()) {
            union {
                decltype(F) p;
                void *addr;
            } u;
            u.p = F;
            remove(u.addr);
        }
    }

    // ── remove ────────────────────────────────────────────────────────────────
    // Unregisters and destroys the Hook for `address`. The Hook destructor
    // unregisters the detour and deletes the HookBase instance, freeing all
    // callback lists. Called automatically when the last callback is removed.
    static void remove(void* address);

    // ── getName ───────────────────────────────────────────────────────────────
    // Extracts a human-readable "Class::method" label from the RTTI type name
    // of the hook stored at `address`.
    static std::string getName(void* address);

    // ── _hooks ────────────────────────────────────────────────────────────────
    // Global map from opaque function address to its live BaseHook.
    // std::unordered_map gives O(1) average lookup.
    static inline std::unordered_map<void*, BaseHook*> _hooks;

public:
    // ── addBefore ─────────────────────────────────────────────────────────────
    // Register a callback to run before function F. Multiple callbacks may be
    // registered per function; by default the callback is appended, but an
    // explicit `position` inserts it at that index (0 = front) instead.
    // Creates the hook automatically on first registration.
    //
    // Compile-time guarantees:
    //   • F must be a free or member function pointer          (HookableFunction)
    //   • Callback signature must match (HookHandle, Args&...) (BeforeCallbackFor)
    template<auto F, typename Callback> requires BeforeCallbackFor<Callback, F>
    static void addBefore(Callback &&callback, std::optional<size_t> position = std::nullopt) {
        getHook<F>()->addBefore(std::forward<Callback>(callback), position);
    }

    // ── removeBefore ──────────────────────────────────────────────────────────
    // Remove the Before callback at `position` (0-based) without needing a
    // HookHandle. No-op if F isn't hooked or position is out of range.
    template<auto F> requires HookableFunction<F>
    static void removeBefore(size_t position) {
        if (auto *hook = findHook<F>()) {
            hook->removeBeforeAt(position);
            tearDownIfEmpty<F>(hook);
        }
    }

    // ── addAfter ──────────────────────────────────────────────────────────────
    // Register a callback to run after function F. Multiple callbacks may be
    // registered per function; by default the callback is appended, but an
    // explicit `position` inserts it at that index (0 = front) instead.
    // Creates the hook automatically on first registration.
    //
    // Compile-time guarantees:
    //   • F must be a free or member function pointer                (HookableFunction)
    //   • Callback signature must match (HookHandle[, R&], Args&...) (AfterCallbackFor)
    template<auto F, typename Callback> requires AfterCallbackFor<Callback, F>
    static void addAfter(Callback &&callback, std::optional<size_t> position = std::nullopt) {
        getHook<F>()->addAfter(std::forward<Callback>(callback), position);
    }

    // ── removeAfter ───────────────────────────────────────────────────────────
    // Remove the After callback at `position` (0-based) without needing a
    // HookHandle. No-op if F isn't hooked or position is out of range.
    template<auto F> requires HookableFunction<F>
    static void removeAfter(size_t position) {
        if (auto *hook = findHook<F>()) {
            hook->removeAfterAt(position);
            tearDownIfEmpty<F>(hook);
        }
    }

    // ── addReplace ────────────────────────────────────────────────────────────
    // Register the (single) callback that completely replaces function F: the
    // original body is never invoked, and the callback itself must produce
    // the return value. Registering again simply overwrites the previous
    // replacement, since only one Replace can exist per function. The
    // callback receives a HookHandle exactly like Before/After, so it can
    // remove itself the same way (handle.remove() inside the callback).
    //
    // Compile-time guarantees:
    //   • F must be a free or member function pointer                     (HookableFunction)
    //   • Callback signature must match (HookHandle, Args&...) -> R       (ReplaceCallbackFor)
    template<auto F, typename Callback> requires ReplaceCallbackFor<Callback, F>
    static void addReplace(Callback &&callback) {
        getHook<F>()->setReplace(std::forward<Callback>(callback));
    }

    // ── removeReplace ─────────────────────────────────────────────────────────
    // Remove the Replace callback for F (if any) without needing its
    // HookHandle. No-op if F isn't hooked or has no Replace registered.
    template<auto F> requires HookableFunction<F>
    static void removeReplace() {
        if (auto *hook = findHook<F>()) {
            hook->clearReplace();
            tearDownIfEmpty<F>(hook);
        }
    }

    // ── addIgnoreConditionally ────────────────────────────────────────────────
    // Register the (single) callback that decides, per call, whether the
    // original body of F should run — like Before, but with a leading bool&
    // the callback sets to skip the call. For non-void F it also receives a
    // mutable result reference to supply a substitute value when it chooses
    // to skip. This is the direct successor to the old callback-based Ignore
    // hook, now capped at one registration per function. Registering again
    // simply overwrites the previous callback.
    //
    // Compile-time guarantees:
    //   • F must be a free or member function pointer                       (HookableFunction)
    //   • Callback signature must match (HookHandle, bool&[, R&], Args&...) (IgnoreConditionallyCallbackFor)
    template<auto F, typename Callback> requires IgnoreConditionallyCallbackFor<Callback, F>
    static void addIgnoreConditionally(Callback &&callback) {
        getHook<F>()->setIgnoreConditionally(std::forward<Callback>(callback));
    }

    // ── removeIgnoreConditionally ─────────────────────────────────────────────
    // Remove the IgnoreConditionally callback for F (if any) without needing
    // its HookHandle. No-op if F isn't hooked or has none registered.
    template<auto F> requires HookableFunction<F>
    static void removeIgnoreConditionally() {
        if (auto *hook = findHook<F>()) {
            hook->clearIgnoreConditionally();
            tearDownIfEmpty<F>(hook);
        }
    }

    // ── addIgnore ─────────────────────────────────────────────────────────────
    // Activate Ignore for function F: the original body stops being called
    // (After callbacks, if any, still run). Only one Ignore state exists per
    // function — it is a toggle, not a callback list — and it takes no
    // callback argument because there is nothing for it to do besides skip
    // the call. Restricted to void-returning functions (VoidHookableFunction):
    // a non-void function has no sensible result to produce when skipped.
    // Safe to call again after removeIgnore() to reactivate.
    template<auto F> requires VoidHookableFunction<F>
    static void addIgnore() {
        getHook<F>()->setIgnoreActive(true);
    }

    // ── removeIgnore ──────────────────────────────────────────────────────────
    // Deactivate Ignore for function F, letting the original body run again.
    // No-op if F isn't hooked or Ignore was never activated.
    template<auto F> requires VoidHookableFunction<F>
    static void removeIgnore() {
        if (auto *hook = findHook<F>()) {
            hook->setIgnoreActive(false);
            tearDownIfEmpty<F>(hook);
        }
    }
};

#endif // CHRYSALIS_HOOKMANAGER_H
