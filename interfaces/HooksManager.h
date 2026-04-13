#ifndef CLOEXTENSIONS_HOOKMANAGER_H
#define CLOEXTENSIONS_HOOKMANAGER_H

#include <unordered_map>
#include <regex>
#include <string>

// ─── undef Qt's emit if it was defined before this header ────────────────────
#ifdef emit
#  undef emit
#endif
#include <polyhook2/Detour/x64Detour.hpp>

#ifdef LOGS_DIR
#   include <Logger.h>
#endif

// =============================================================================
//  HookHandle
// =============================================================================
class HookHandle {
    friend class HooksManager;
    std::list<std::function<void()> > *_executeLater;
    std::function<void()> _remover;
    HookHandle(std::list<std::function<void()> > &executeLater,
               std::function<void()> remover)
        : _executeLater(&executeLater), _remover(std::move(remover)) {}
public:
    void remove() const { _executeLater->push_back(_remover); }
};

// =============================================================================
//  hook_detail
// =============================================================================
namespace hook_detail {

    template<typename R, typename... ExtraArgs>
    struct AfterType {
        using type = std::function<void(HookHandle, R &, ExtraArgs &...)>;
    };
    template<typename... ExtraArgs>
    struct AfterType<void, ExtraArgs...> {
        using type = std::function<void(HookHandle, ExtraArgs &...)>;
    };

    template<typename T> struct FuncTraits;

    template<typename R, typename... Args>
    struct FuncTraits<R(*)(Args...)> {
        using Before = std::function<void(HookHandle, Args &...)>;
        using After  = typename AfterType<R, Args...>::type;
    };

    template<typename R, typename Class, typename... Args>
    struct FuncTraits<R(Class::*)(Args...)> {
        using Before = std::function<void(HookHandle, Class *&, Args &...)>;
        using After  = typename AfterType<R, Class *, Args...>::type;
    };

    template<typename R, typename Class, typename... Args>
    struct FuncTraits<R(Class::*)(Args...) const> {
        using Before = std::function<void(HookHandle, const Class *&, Args &...)>;
        using After  = typename AfterType<R, const Class *, Args...>::type;
    };

    // ── needs_retbuf_v<T> ─────────────────────────────────────────────────────
    // MSVC x64 ABI: a member function returning a non-trivially-copyable type
    // (or one larger than a pointer) uses a hidden return-buffer pointer as the
    // SECOND argument (after `this`).  The function is void at the binary level.
    //
    // Example — QSettings::value:
    //   C++ declaration:   QVariant value(const QString&, const QVariant&) const
    //   Binary layout:     void     value(QSettings* this,    // RCX
    //                                     QVariant*  retbuf,  // RDX  ← hidden
    //                                     const QString& key, // R8
    //                                     const QVariant& def)// R9
    //
    // A hook function must match this layout exactly or RCX/RDX are swapped,
    // causing the hook to treat the retbuf pointer as `this` → crash.
    template<typename T>
    constexpr bool needs_retbuf_v =
        !std::is_void_v<T> &&
        (!std::is_trivially_copyable_v<T> || sizeof(T) > sizeof(void*));

} // namespace hook_detail

// =============================================================================
//  Concepts
// =============================================================================
template<auto F>
concept HookableFunction =
    std::is_member_function_pointer_v<decltype(F)> ||
    (std::is_pointer_v<decltype(F)> &&
     std::is_function_v<std::remove_pointer_t<decltype(F)>>);

template<typename Cb, auto F>
concept BeforeCallbackFor =
    HookableFunction<F> &&
    std::convertible_to<Cb, typename hook_detail::FuncTraits<decltype(F)>::Before>;

template<typename Cb, auto F>
concept AfterCallbackFor =
    HookableFunction<F> &&
    std::convertible_to<Cb, typename hook_detail::FuncTraits<decltype(F)>::After>;

// =============================================================================
//  HooksManager
// =============================================================================
class HooksManager {
    inline static std::string LOGGER_NAME_ = "Hooks Manager";

    // ── AbstractHook ──────────────────────────────────────────────────────────
    class AbstractHook {
    public:
        explicit AbstractHook(const uint64_t function, const uint64_t hook, uint64_t *original)
            : _detour(function, hook, original) {}

        void install() {
            // Exclude INPLACE/INPLACE_SHORT: they overwrite 16-24+ prologue bytes,
            // which can include RIP-relative instructions.  PolyHook then generates
            // a translation routine with `ret 0x80` that corrupts the caller's stack.
            // VALLOC2 and CODE_CAVE use a 6-byte near-jump — safe for all prologues.
            _detour.setDetourScheme(
                static_cast<PLH::x64Detour::detour_scheme_t>(
                    PLH::x64Detour::VALLOC2 | PLH::x64Detour::CODE_CAVE));
            _detour.hook();
        }

        virtual ~AbstractHook() { _detour.unHook(); }

    protected:
        PLH::x64Detour _detour;
    };

    template<auto Function>
    struct HookTraits;

    // =========================================================================
    //  HookBase — for functions whose return value fits in a register
    //  (void, bool, int, pointer, small trivially-copyable struct, etc.)
    // =========================================================================
    template<typename R, typename Original, typename... CallArgs>
    struct HookBase {
        using Before = std::function<void(HookHandle, CallArgs &...)>;
        using After  = typename hook_detail::AfterType<R, CallArgs...>::type;

        std::list<Before> _before;
        std::list<After>  _after;
        std::list<std::function<void()>> _executeLater;
        void* _address = nullptr;

        void addBefore(Before cb) { _before.push_back(std::move(cb)); }
        void addAfter (After  cb) { _after .push_back(std::move(cb)); }

        template<typename T, typename... Args>
        void iterate(std::list<T>& list, Args&... args) {
            for (auto it = list.begin(); it != list.end(); ++it) {
                (*it)(HookHandle(_executeLater, [this, &list, it] {
#ifdef LOGS_DIR
                    LOG_DEBUG_TO(HooksManager::LOGGER_NAME_,
                        "Removing callback for hook: {}", getName(_address));
#endif
                    list.erase(it);
                    if (_before.empty() && _after.empty()) {
#ifdef LOGS_DIR
                        LOG_DEBUG_TO(HooksManager::LOGGER_NAME_,
                            "No callbacks left — detaching hook: {}", getName(_address));
#endif
                        remove(_address);
                    }
                }), args...);
            }
        }

        static R hook(CallArgs... args) {
            std::list<std::function<void()>> pending;
            std::swap(_instance->_executeLater, pending);
            for (auto& f : pending) f();

            auto* inst = _instance;
            inst->iterate(inst->_before, args...);

            if constexpr (std::is_void_v<R>) {
                original(args...);
                if (_instance) inst->iterate(inst->_after, args...);
            } else {
                R result = original(args...);
                if (_instance) inst->iterate(inst->_after, result, args...);
                return result;
            }
        }

        static inline Original original = nullptr;
        static inline HookBase* _instance = nullptr;
    };

    // =========================================================================
    //  HookBaseRetbuf — for member functions whose return type requires a
    //  hidden return-buffer pointer (needs_retbuf_v<R> == true).
    //
    //  MSVC x64 binary layout:  void func(ClassPtr this, R* retbuf, Args...)
    //  RCX = this,  RDX = retbuf,  R8/R9 = explicit args.
    //
    //  The user-facing Before/After callback API is identical to HookBase:
    //    Before: (HookHandle, ClassPtr&, Args&...)      — retbuf not exposed
    //    After:  (HookHandle, R&, ClassPtr&, Args&...)  — *retbuf passed as R&
    // =========================================================================
    template<typename R, typename ClassPtr, typename... Args>
    struct HookBaseRetbuf {
        using Before = std::function<void(HookHandle, ClassPtr&, Args&...)>;
        using After  = typename hook_detail::AfterType<R, ClassPtr, Args...>::type;

        std::list<Before> _before;
        std::list<After>  _after;
        std::list<std::function<void()>> _executeLater;
        void* _address = nullptr;

        void addBefore(Before cb) { _before.push_back(std::move(cb)); }
        void addAfter (After  cb) { _after .push_back(std::move(cb)); }

        template<typename T, typename... Ts>
        void iterate(std::list<T>& list, Ts&... ts) {
            for (auto it = list.begin(); it != list.end(); ++it) {
                (*it)(HookHandle(_executeLater, [this, &list, it] {
#ifdef LOGS_DIR
                    LOG_DEBUG_TO(HooksManager::LOGGER_NAME_,
                        "Removing callback for hook: {}", getName(_address));
#endif
                    list.erase(it);
                    if (_before.empty() && _after.empty()) {
#ifdef LOGS_DIR
                        LOG_DEBUG_TO(HooksManager::LOGGER_NAME_,
                            "No callbacks left — detaching hook: {}", getName(_address));
#endif
                        remove(_address);
                    }
                }), ts...);
            }
        }

        // Binary signature matches MSVC x64 retbuf ABI: void(ClassPtr, R*, Args...)
        static void hook(ClassPtr self, R* retbuf, Args... args) {
            std::list<std::function<void()>> pending;
            std::swap(_instance->_executeLater, pending);
            for (auto& f : pending) f();

            auto* inst = _instance;
            if (inst) inst->iterate(inst->_before, self, args...);

            original(self, retbuf, args...);  // fills *retbuf in-place

            if (_instance) inst->iterate(inst->_after, *retbuf, self, args...);
        }

        using Original = void(*)(ClassPtr, R*, Args...);
        static inline Original    original  = nullptr;
        static inline HookBaseRetbuf* _instance = nullptr;
    };

    // ── Hook<Target> ──────────────────────────────────────────────────────────
    template<auto Target> requires HookableFunction<Target>
    struct Hook : AbstractHook {
        explicit Hook(void* address)
            : AbstractHook(
                HookTraits<Target>::address(),
                reinterpret_cast<uint64_t>(&HookTraits<Target>::hook),
                reinterpret_cast<uint64_t*>(&HookTraits<Target>::original)) {
            auto* inst = new HookTraits<Target>();
            inst->_address = address;
            HookTraits<Target>::_instance = inst;
            install();
        }

        ~Hook() override {
            delete static_cast<HookTraits<Target>*>(HookTraits<Target>::_instance);
            HookTraits<Target>::_instance = nullptr;
        }

        void addBefore(typename HookTraits<Target>::Before cb) {
            HookTraits<Target>::_instance->addBefore(std::move(cb));
        }
        void addAfter(typename HookTraits<Target>::After cb) {
            HookTraits<Target>::_instance->addAfter(std::move(cb));
        }
    };

    // ── HookTraits: free function ─────────────────────────────────────────────
    template<typename R, typename... Args, R(*Function)(Args...)>
    struct HookTraits<Function> : HookBase<R, R(*)(Args...), Args...> {
        static uint64_t address() { return reinterpret_cast<uint64_t>(Function); }
    };

    // ── HookTraits: non-const member, small/trivial return ────────────────────
    template<typename R, typename Class, typename... Args, R(Class::*Function)(Args...)>
        requires (!hook_detail::needs_retbuf_v<R>)
    struct HookTraits<Function> : HookBase<R, R(*)(Class*, Args...), Class*, Args...> {
        static uint64_t address() {
            union { R(Class::*mfp)(Args...); uint64_t addr; } u;
            u.mfp = Function; return u.addr;
        }
    };

    // ── HookTraits: non-const member, large/non-trivial return (retbuf) ───────
    // Binary layout: void func(Class* this, R* retbuf, Args...)
    template<typename R, typename Class, typename... Args, R(Class::*Function)(Args...)>
        requires (hook_detail::needs_retbuf_v<R>)
    struct HookTraits<Function> : HookBaseRetbuf<R, Class*, Args...> {
        static uint64_t address() {
            union { R(Class::*mfp)(Args...); uint64_t addr; } u;
            u.mfp = Function; return u.addr;
        }
    };

    // ── HookTraits: const member, small/trivial return ────────────────────────
    template<typename R, typename Class, typename... Args, R(Class::*Function)(Args...) const>
        requires (!hook_detail::needs_retbuf_v<R>)
    struct HookTraits<Function> : HookBase<R, R(*)(const Class*, Args...), const Class*, Args...> {
        static uint64_t address() {
            union { R(Class::*mfp)(Args...) const; uint64_t addr; } u;
            u.mfp = Function; return u.addr;
        }
    };

    // ── HookTraits: const member, large/non-trivial return (retbuf) ──────────
    // Confirmed by QSettings::value disassembly:
    //   RCX = QSettings* this,  RDX = QVariant* retbuf,
    //   R8  = const QString& key,  R9 = const QVariant& defaultValue
    template<typename R, typename Class, typename... Args, R(Class::*Function)(Args...) const>
        requires (hook_detail::needs_retbuf_v<R>)
    struct HookTraits<Function> : HookBaseRetbuf<R, const Class*, Args...> {
        static uint64_t address() {
            union { R(Class::*mfp)(Args...) const; uint64_t addr; } u;
            u.mfp = Function; return u.addr;
        }
    };

    // ── getHook ───────────────────────────────────────────────────────────────
    template<auto F> requires HookableFunction<F>
    static Hook<F>* getHook() {
        union { decltype(F) p; void* addr; } u;
        u.p = F;
        const auto it = _hooks.find(u.addr);
        if (it == _hooks.end()) {
            auto* hook = new Hook<F>(u.addr);
            _hooks[u.addr] = hook;
#ifdef LOGS_DIR
            LOG_INFO_TO(HooksManager::LOGGER_NAME_, "Hook created: {}", getName(u.addr));
#endif
            return hook;
        }
        return dynamic_cast<Hook<F>*>(it->second);
    }

    static void remove(void* address) {
        const auto it = _hooks.find(address);
        if (it == _hooks.end()) return;
        const auto* hook = it->second;
        _hooks.erase(it);
        delete hook;
    }

    static std::string getName(void* address) {
        const auto it = _hooks.find(address);
        if (it == _hooks.end()) return "<unknown>";
        std::string raw = typeid(*it->second).name();
        static const std::regex re(R"(<[^>]*?(\w+::\w+)\()");
        std::smatch match;
        if (std::regex_search(raw, match, re) && match.size() > 1)
            return match[1].str();
        return raw;
    }

    static inline std::unordered_map<void*, AbstractHook*> _hooks;

public:
    template<auto F, typename Callback> requires BeforeCallbackFor<Callback, F>
    static void addBefore(Callback&& callback) {
        getHook<F>()->addBefore(std::forward<Callback>(callback));
    }

    template<auto F, typename Callback> requires AfterCallbackFor<Callback, F>
    static void addAfter(Callback&& callback) {
        getHook<F>()->addAfter(std::forward<Callback>(callback));
    }
};

#endif // CLOEXTENSIONS_HOOKMANAGER_H
