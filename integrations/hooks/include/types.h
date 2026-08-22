#ifndef CHRYSALIS_TYPES_H
#define CHRYSALIS_TYPES_H

#include "HookHandle.h"

// =============================================================================
//  type-level traits for concepts
//
//  MSVC cannot deduce partial specializations of templates whose non-type
//  template parameter is a member function pointer (e.g. Traits<&Foo::bar>).
//  The workaround is to specialize on the pointer *type* via decltype(F),
//  which uses ordinary type-level partial specialization that all compilers
//  handle reliably.
// =============================================================================

// ── AfterType<R, ExtraArgs...> ────────────────────────────────────────────────
// Lazily builds the After std::function signature.
// std::conditional_t is NOT used here because it instantiates both branches
// eagerly — forming std::function<void(HookHandle, void&, ...)> is ill-formed.
// Partial specialization on void avoids that instantiation entirely.
template <typename R, typename... ExtraArgs>
struct AfterType {
    // Non-void: callback receives the return value as a mutable ref first.
    using type = std::function<void(HookHandle, R&, ExtraArgs&...)>;
};

template <typename... ExtraArgs>
struct AfterType<void, ExtraArgs...> {
    // Void: no return value parameter.
    using type = std::function<void(HookHandle, ExtraArgs&...)>;
};

// ── ReplaceType<R, ExtraArgs...> ──────────────────────────────────────────────
// Builds the Replace std::function signature: the callback fully replaces
// the original function body, so it receives the (mutable) call arguments
// and must itself produce the return value — no void-split needed since R
// is simply the function's own return type here (possibly void).
template <typename R, typename... ExtraArgs>
struct ReplaceType {
    using type = std::function<R(HookHandle, ExtraArgs&...)>;
};

// ── IgnoreConditionallyType<R, ExtraArgs...> ──────────────────────────────────
// Builds the IgnoreConditionally callback signature: like Before, it sees
// every call argument by reference, plus a leading bool& the callback sets
// to decide (per-call) whether the original should run. For non-void R a
// ResultArg is also exposed so the callback can supply a substitute result
// when it chooses to skip the original — reference returns use a pointer
// since a reference cannot be default-initialized before the real call.
template <typename R, typename... ExtraArgs>
struct IgnoreConditionallyType {
    using ResultArg = std::conditional_t<std::is_reference_v<R>, std::remove_reference_t<R>*, R>;
    using type = std::function<void(HookHandle, bool&, ResultArg&, ExtraArgs&...)>;
};

template <typename... ExtraArgs>
struct IgnoreConditionallyType<void, ExtraArgs...> {
    using type = std::function<void(HookHandle, bool&, ExtraArgs&...)>;
};

// ── FuncTraits<T> — undefined base (SFINAE / concept failure for bad T) ──────
template <typename T>
struct FuncTraits;

// ── Free function: R(*)(Args...) ──────────────────────────────────────────────
template <typename R, typename... Args>
struct FuncTraits<R (*)(Args...)> {
    using ReturnType = R;
    using Before = std::function<void(HookHandle, Args&...)>;
    using After = AfterType<R, Args...>::type;
    using Replace = ReplaceType<R, Args...>::type;
    using IgnoreConditionally = IgnoreConditionallyType<R, Args...>::type;
};

// ── Non-const member function: R(Class::*)(Args...) ──────────────────────────
template <typename R, typename Class, typename... Args>
struct FuncTraits<R (Class::*)(Args...)> {
    using ReturnType = R;
    using Before = std::function<void(HookHandle, Class*&, Args&...)>;
    using After = AfterType<R, Class*, Args...>::type;
    using Replace = ReplaceType<R, Class*, Args...>::type;
    using IgnoreConditionally = IgnoreConditionallyType<R, Class*, Args...>::type;
};

// ── Const member function: R(Class::*)(Args...) const ────────────────────────
// The callback types here (Before/After/Replace/IgnoreConditionally) are
// uniform for every R — trivial, non-trivial, or void — and never expose
// a raw pointer to the return value. Non-trivial R needs extra care at
// the HookTraits level below (where the actual trampoline/hook() ABI is
// handled), but that's entirely internal and doesn't affect this type.
template <typename R, typename Class, typename... Args>
struct FuncTraits<R (Class::*)(Args...) const> {
    using ReturnType = R;
    using Before = std::function<void(HookHandle, const Class*&, Args&...)>;
    using After = AfterType<R, const Class*, Args...>::type;
    using Replace = ReplaceType<R, const Class*, Args...>::type;
    using IgnoreConditionally = IgnoreConditionallyType<R, const Class*, Args...>::type;
};

// ── Noexcept free function: R(*)(Args...) noexcept ───────────────────────────
template <typename R, typename... Args>
struct FuncTraits<R (*)(Args...) noexcept> {
    using ReturnType = R;
    using Before = std::function<void(HookHandle, Args&...)>;
    using After = AfterType<R, Args...>::type;
    using Replace = ReplaceType<R, Args...>::type;
    using IgnoreConditionally = IgnoreConditionallyType<R, Args...>::type;
};

// ── Noexcept non-const member function: R(Class::*)(Args...) noexcept ────────
template <typename R, typename Class, typename... Args>
struct FuncTraits<R (Class::*)(Args...) noexcept> {
    using ReturnType = R;
    using Before = std::function<void(HookHandle, Class*&, Args&...)>;
    using After = AfterType<R, Class*, Args...>::type;
    using Replace = ReplaceType<R, Class*, Args...>::type;
    using IgnoreConditionally = IgnoreConditionallyType<R, Class*, Args...>::type;
};

// ── Noexcept const member function: R(Class::*)(Args...) const noexcept ──────
template <typename R, typename Class, typename... Args>
struct FuncTraits<R (Class::*)(Args...) const noexcept> {
    using ReturnType = R;
    using Before = std::function<void(HookHandle, const Class*&, Args&...)>;
    using After = AfterType<R, const Class*, Args...>::type;
    using Replace = ReplaceType<R, const Class*, Args...>::type;
    using IgnoreConditionally = IgnoreConditionallyType<R, const Class*, Args...>::type;
};

// =============================================================================
//  Concepts
// =============================================================================

// ── HookableFunction<F> ───────────────────────────────────────────────────────
// F must be a free function pointer or a (possibly const) member function
// pointer. Implemented via standard type traits to avoid MSVC's partial
// specialization deduction issues with member function pointer NTTPs.
template <auto F>
concept HookableFunction = std::is_member_function_pointer_v<decltype(F)> ||
    (std::is_pointer_v<decltype(F)> && std::is_function_v<std::remove_pointer_t<decltype(F)>>);

// ── VoidHookableFunction<F> ───────────────────────────────────────────────────
// F must be hookable AND return void. The Ignore feature only makes sense for
// void functions: there is no result to fabricate when the original call is
// skipped, so the API is restricted at compile time to this subset.
template <auto F>
concept VoidHookableFunction = HookableFunction<F> && std::is_void_v<typename FuncTraits<decltype(F)>::ReturnType>;

// ── BeforeCallbackFor<Cb, F> ──────────────────────────────────────────────────
// Cb must be implicitly convertible to the expected Before callback type for F.
// Gives a readable error at the addBefore call site when the signature is wrong.
template <typename Cb, auto F>
concept BeforeCallbackFor = HookableFunction<F> && std::convertible_to<Cb, typename FuncTraits<decltype(F)>::Before>;

// ── AfterCallbackFor<Cb, F> ───────────────────────────────────────────────────
// Same as above for After callbacks, which additionally carry the return value
// (if non-void) as a first mutable reference before the call arguments.
template <typename Cb, auto F>
concept AfterCallbackFor = HookableFunction<F> && std::convertible_to<Cb, typename FuncTraits<decltype(F)>::After>;

// ── ReplaceCallbackFor<Cb, F> ─────────────────────────────────────────────────
// Cb must be implicitly convertible to the expected Replace callback type for
// F: it receives the call arguments and must produce the return value itself,
// since (unlike Before/After) the original function is never invoked.
template <typename Cb, auto F>
concept ReplaceCallbackFor = HookableFunction<F> && std::convertible_to<Cb, typename FuncTraits<decltype(F)>::Replace>;

// ── IgnoreConditionallyCallbackFor<Cb, F> ─────────────────────────────────────
// Cb must be implicitly convertible to the expected IgnoreConditionally
// callback type for F: like Before, plus a leading bool& the callback sets to
// decide per-call whether the original should be skipped.
template <typename Cb, auto F>
concept IgnoreConditionallyCallbackFor =
    HookableFunction<F> && std::convertible_to<Cb, typename FuncTraits<decltype(F)>::IgnoreConditionally>;

#endif // CHRYSALIS_TYPES_H
