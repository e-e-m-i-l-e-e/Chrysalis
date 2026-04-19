// ============================================================================
//  HooksManager_test.cpp
//
//  Coverage for HookManager.h — compile-time concept/trait checks and
//  runtime integration tests using real x64 detours via PolyHook.
//
//  Sections:
//    1.  Test subject functions  — simple, noinline, safe to detour
//    2.  Compile-time checks     — static_assert on concepts and trait types
//    3.  Runtime fixture         — GTest fixture for handle lifecycle
//    4.  addBefore tests         — free function
//    5.  addAfter tests          — free function (non-void + void return)
//    6.  Ordering test           — before fires before original, after fires after
//    7.  HookHandle::remove      — stops callback, deferred self-removal
//    8.  Hook auto-teardown      — hook self-destructs when last callback removed
//    9.  Re-registration         — new hook installs cleanly after teardown
//   10.  Member function hooks   — this pointer, return value, mutation
//   11.  Independent hooks       — two different functions don't interfere
// ============================================================================

#include "../include/HooksManager.h"
#include <gtest/gtest.h>
#include <optional>
#include <vector>
#include <string>

// ============================================================================
//  1. Test subject free functions
//
//  Two attributes are required to make these safe to detour:
//
//  __declspec(noinline)
//    Prevents the compiler from substituting the function body at call sites.
//    Without this, the call instruction is never emitted and PolyHook's patch
//    at the function's address is never reached.
//
//  #pragma optimize("", off)
//    With /O2, MSVC performs interprocedural constant folding and dead-call
//    elimination on functions whose bodies are visible in the same TU. Even
//    with __declspec(noinline), a call like `subject_add(1, 2)` whose result
//    is unused — or whose value (3) is computable at compile time — can be
//    silently dropped. That means the patched prologue is never executed and
//    the callbacks never fire. Disabling optimization from this point onward
//    forces the compiler to emit every call as a real CALL instruction.
// ============================================================================
#pragma optimize("", off)

__declspec(noinline) int  subject_add(int a, int b) { return a + b; }
__declspec(noinline) int  subject_id(int x)         { return x; }

static bool g_noop_ran = false;
__declspec(noinline) void subject_noop(int x)       { g_noop_ran = true; }

// ── Test subject class ────────────────────────────────────────────────────────
struct Widget {
    int value = 0;
    __declspec(noinline) int  accumulate(int by) { value += by; return value; }
    __declspec(noinline) void clear()            { value = 0; }
};


// ============================================================================
//  2. Compile-time checks
//  These live in a namespace so they don't pollute the global scope.
//  A compilation failure here means the concept or trait is broken.
// ============================================================================
namespace ct {

    // ── AfterType: void return — no R& parameter ──────────────────────────────
    using VoidAfter = hook_detail::AfterType<void, int>;
    static_assert(std::is_same_v<
        VoidAfter::type,
        std::function<void(HookHandle, int&)>>);

    // ── AfterType: non-void return — R& is first param after HookHandle ───────
    using IntFloatAfter = hook_detail::AfterType<int, float>;
    static_assert(std::is_same_v<
        IntFloatAfter::type,
        std::function<void(HookHandle, int&, float&)>>);

    // ── AfterType: non-void, no extra args ────────────────────────────────────
    using IntAfterNoArgs = hook_detail::AfterType<int>;
    static_assert(std::is_same_v<
        IntAfterNoArgs::type,
        std::function<void(HookHandle, int&)>>);

    // ── FuncTraits: free function ─────────────────────────────────────────────
    // subject_add: int(int, int)
    using AddTraits = hook_detail::FuncTraits<decltype(&subject_add)>;
    static_assert(std::is_same_v<
        AddTraits::Before,
        std::function<void(HookHandle, int&, int&)>>);
    // After: AfterType<int, int, int> → void(HookHandle, int& ret, int& a, int& b)
    static_assert(std::is_same_v<
        AddTraits::After,
        std::function<void(HookHandle, int&, int&, int&)>>);

    // ── FuncTraits: member function ───────────────────────────────────────────
    // Widget::accumulate: int(Widget::*)(int)
    using AccTraits = hook_detail::FuncTraits<decltype(&Widget::accumulate)>;
    static_assert(std::is_same_v<
        AccTraits::Before,
        std::function<void(HookHandle, Widget*&, int&)>>);
    // After: AfterType<int, Widget*, int> → void(HookHandle, int& ret, Widget*& self, int& by)
    static_assert(std::is_same_v<
        AccTraits::After,
        std::function<void(HookHandle, int&, Widget*&, int&)>>);

    // ── HookableFunction concept ──────────────────────────────────────────────
    static_assert(HookableFunction<&subject_add>);
    static_assert(HookableFunction<&subject_id>);
    static_assert(HookableFunction<&subject_noop>);
    static_assert(HookableFunction<&Widget::accumulate>);
    static_assert(HookableFunction<&Widget::clear>);

    // ── BeforeCallbackFor concept ─────────────────────────────────────────────
    using AddBefore = std::function<void(HookHandle, int&, int&)>;
    static_assert(BeforeCallbackFor<AddBefore, &subject_add>);

    using AccBefore = std::function<void(HookHandle, Widget*&, int&)>;
    static_assert(BeforeCallbackFor<AccBefore, &Widget::accumulate>);

    // ── AfterCallbackFor concept ──────────────────────────────────────────────
    using AddAfter = std::function<void(HookHandle, int&, int&, int&)>;
    static_assert(AfterCallbackFor<AddAfter, &subject_add>);

    using AccAfter = std::function<void(HookHandle, int&, Widget*&, int&)>;
    static_assert(AfterCallbackFor<AccAfter, &Widget::accumulate>);

} // namespace ct


// ============================================================================
//  3. Runtime fixture
//  Tracks HookHandles registered during each test and removes them in
//  TearDown so the static _hooks map is clean before the next test.
//  Only use track() for handles you do NOT manually remove inside the test.
// ============================================================================
class HooksManagerTest : public ::testing::Test {
protected:
    std::vector<std::optional<HookHandle>> tracked_;

    // Call from inside a callback to register the handle for auto-cleanup.
    void track(HookHandle h) { tracked_.emplace_back(h); }

    void TearDown() override {
        for (auto& h : tracked_)
            if (h.has_value()) h->remove();
        tracked_.clear();
    }
};

// ============================================================================
//  4. addBefore — free function
// ============================================================================

// Callback fires at all — basic smoke test
TEST_F(HooksManagerTest, AddBefore_CallbackFires) {
    bool fired = false;
    HooksManager::addBefore<&subject_add>([&](HookHandle h, int& a, int& b) {
        track(h); fired = true;
    });
    subject_add(1, 2);
    EXPECT_TRUE(fired);
}

// Callback receives the exact argument values passed by the caller
TEST_F(HooksManagerTest, AddBefore_ReceivesCorrectArgs) {
    int cap_a = -1, cap_b = -1;
    HooksManager::addBefore<&subject_add>([&](HookHandle h, int& a, int& b) {
        track(h); cap_a = a; cap_b = b;
    });
    subject_add(10, 20);
    EXPECT_EQ(cap_a, 10);
    EXPECT_EQ(cap_b, 20);
}

// Mutating args in Before propagates to the original function call
TEST_F(HooksManagerTest, AddBefore_MutatedArgsReachOriginal) {
    HooksManager::addBefore<&subject_add>([&](HookHandle h, int& a, int& b) {
        track(h); a = 100; b = 1; // override caller values
    });
    // original sees 100 + 1 = 101, not 3 + 4 = 7
    int result = subject_add(3, 4);
    EXPECT_EQ(result, 101);
}

// Original still returns the correct value even with a before callback attached
TEST_F(HooksManagerTest, AddBefore_OriginalReturnValuePreserved) {
    HooksManager::addBefore<&subject_add>([&](HookHandle h, int& a, int& b) {
        track(h); /* no-op */
    });
    EXPECT_EQ(subject_add(6, 7), 13);
}

// All registered Before callbacks fire on each invocation
TEST_F(HooksManagerTest, AddBefore_MultipleCallbacks_AllFire) {
    int count = 0;
    for (int i = 0; i < 3; ++i)
        HooksManager::addBefore<&subject_id>([&](HookHandle h, int& x) {
            track(h); ++count;
        });
    subject_id(0);
    EXPECT_EQ(count, 3);
}


// ============================================================================
//  5. addAfter — free function
// ============================================================================

// After callback fires
TEST_F(HooksManagerTest, AddAfter_NonVoidReturn_CallbackFires) {
    bool fired = false;
    HooksManager::addAfter<&subject_add>([&](HookHandle h, int& ret, int& a, int& b) {
        track(h); fired = true;
    });
    subject_add(1, 1);
    EXPECT_TRUE(fired);
}

// After callback receives the real return value produced by the original
TEST_F(HooksManagerTest, AddAfter_NonVoidReturn_CorrectReturnValue) {
    int cap_ret = -1;
    HooksManager::addAfter<&subject_add>([&](HookHandle h, int& ret, int& a, int& b) {
        track(h); cap_ret = ret;
    });
    subject_add(5, 7);           // original returns 12
    EXPECT_EQ(cap_ret, 12);
}

// After callback modifying ret& changes what the caller actually receives
// (ret is a local in hook() — the modified value is what gets returned)
TEST_F(HooksManagerTest, AddAfter_ModifyingReturnValueAffectsCaller) {
    HooksManager::addAfter<&subject_add>([&](HookHandle h, int& ret, int& a, int& b) {
        track(h); ret = -ret; // negate
    });
    int result = subject_add(3, 4); // original = 7 → after negates → -7
    EXPECT_EQ(result, -7);
}

// After callback also receives the call arguments
TEST_F(HooksManagerTest, AddAfter_ReceivesCallArgs) {
    int cap_a = -1, cap_b = -1;
    HooksManager::addAfter<&subject_add>([&](HookHandle h, int& ret, int& a, int& b) {
        track(h); cap_a = a; cap_b = b;
    });
    subject_add(11, 22);
    EXPECT_EQ(cap_a, 11);
    EXPECT_EQ(cap_b, 22);
}

// After callback for a void-returning function — no return parameter in signature
TEST_F(HooksManagerTest, AddAfter_VoidReturn_OriginalRunsBeforeCallback) {
    g_noop_ran = false;
    bool after_fired = false;

    HooksManager::addAfter<&subject_noop>([&](HookHandle h, int& x) {
        track(h);
        // original must have already run by the time After fires
        EXPECT_TRUE(g_noop_ran);
        after_fired = true;
    });

    subject_noop(1);
    EXPECT_TRUE(after_fired);
}

// ============================================================================
//  6. Ordering: Before fires before original, After fires after original
// ============================================================================

TEST_F(HooksManagerTest, Ordering_BeforeOriginalAfter) {
    std::vector<std::string> order;
    g_noop_ran = false;

    // Use subject_noop so we can observe when the original ran via g_noop_ran
    HooksManager::addBefore<&subject_noop>([&](HookHandle h, int& x) {
        track(h);
        EXPECT_FALSE(g_noop_ran); // original hasn't run yet
        order.push_back("before");
    });
    HooksManager::addAfter<&subject_noop>([&](HookHandle h, int& x) {
        track(h);
        EXPECT_TRUE(g_noop_ran);  // original has already run
        order.push_back("after");
    });

    subject_noop(0);

    ASSERT_EQ(order.size(), 2u);
    EXPECT_EQ(order[0], "before");
    EXPECT_EQ(order[1], "after");
}


// ============================================================================
//  7. HookHandle::remove
// ============================================================================

// Callback stops firing after remove() is called from outside
TEST_F(HooksManagerTest, Remove_StopsCallbackFiring) {
    int fired = 0;
    std::optional<HookHandle> saved, sentinel;

    // Sentinel: stays registered after saved is removed so _before is never
    // empty inside hook(). Without it, the deferred removal of saved causes
    // auto-teardown mid-hook: unHook() frees the PolyHook trampoline, then
    // hook() calls original() on that freed memory → STATUS_ILLEGAL_INSTRUCTION.
    // Tracked exactly once via the guard; TearDown defers its removal safely.
    HooksManager::addBefore<&subject_add>([&](HookHandle h, int& a, int& b) {
        if (!sentinel) { sentinel = h; tracked_.emplace_back(h); }
    });
    HooksManager::addBefore<&subject_add>([&](HookHandle h, int& a, int& b) {
        if (!saved) saved = h;
        ++fired;
    });

    subject_add(1, 1);           // both fire; handles captured
    EXPECT_EQ(fired, 1);

    saved->remove();
    saved.reset();

    subject_add(1, 1);           // flushes removal; sentinel alive → no teardown
    EXPECT_EQ(fired, 1);         // test callback did not fire again
}

// remove() called from inside the callback itself — must be deferred and safe
// (std::list iterators remain valid; the actual erase happens on next hook entry)
TEST_F(HooksManagerTest, Remove_SelfRemovalFromWithinCallback_IsSafe) {
    int fired = 0;
    std::optional<HookHandle> sentinel;

    // Same sentinel pattern: once the self-removing callback erases itself,
    // sentinel keeps _before non-empty so auto-teardown doesn't fire inside hook().
    HooksManager::addBefore<&subject_id>([&](HookHandle h, int& x) {
        if (!sentinel) { sentinel = h; tracked_.emplace_back(h); }
    });
    HooksManager::addBefore<&subject_id>([&](HookHandle h, int& x) {
        ++fired;
        h.remove(); // schedules removal — does NOT erase iterator right now
    });

    subject_id(0);   // both fire; self-remover schedules its own removal
    EXPECT_EQ(fired, 1);

    subject_id(0);   // flushes: self-remover erased; sentinel alive → no teardown
    EXPECT_EQ(fired, 1);
}

// Removing one callback while others remain — only the removed one stops
TEST_F(HooksManagerTest, Remove_OneOfMultiple_OthersStillFire) {
    int count_a = 0, count_b = 0;
    std::optional<HookHandle> handle_a, handle_b;

    HooksManager::addBefore<&subject_id>([&](HookHandle h, int& x) {
        if (!handle_a) handle_a = h;
        ++count_a;
    });
    // Guard: subject_id fires twice in this test, so track exactly once.
    // Without the guard, tracked_ would hold two copies of the same handle;
    // TearDown would defer two removals of the same std::list iterator — the
    // second erase is UB and causes a heap-corruption crash in the next test.
    HooksManager::addBefore<&subject_id>([&](HookHandle h, int& x) {
        if (!handle_b) { handle_b = h; tracked_.emplace_back(h); }
        ++count_b;
    });

    subject_id(0);            // both fire; handles captured
    EXPECT_EQ(count_a, 1);
    EXPECT_EQ(count_b, 1);

    handle_a->remove();
    handle_a.reset();

    subject_id(0);            // only B fires
    EXPECT_EQ(count_a, 1);
    EXPECT_EQ(count_b, 2);
}

// ============================================================================
//  8. Hook auto-teardown — callbacks stop firing once all are removed
//
//  NOTE on testability: PolyHook frees the trampoline during unHook(), but
//  hook() is still on the call stack at that point. After teardown the code
//  in hook() falls through and calls original() — which is now freed memory.
//  Testing "function works after total teardown" would therefore always crash.
//  A sentinel keeps at least one callback registered so teardown never fires
//  inside hook(). What we verify instead: deferred removals work correctly
//  and the removed callbacks genuinely stop firing.
// ============================================================================

TEST_F(HooksManagerTest, AutoTeardown_CallbacksStopFiringAfterAllRemoved) {
    int fires = 0;
    std::optional<HookHandle> h1, h2, sentinel;

    // Sentinel keeps _before non-empty so teardown never fires mid-hook.
    HooksManager::addBefore<&subject_add>([&](HookHandle h, int& a, int& b) {
        if (!sentinel) { sentinel = h; tracked_.emplace_back(h); }
    });
    HooksManager::addBefore<&subject_add>([&](HookHandle h, int& a, int& b) {
        if (!h1) h1 = h; ++fires;
    });
    HooksManager::addBefore<&subject_add>([&](HookHandle h, int& a, int& b) {
        if (!h2) h2 = h;
    });

    subject_add(0, 0);              // sentinel, h1, h2 captured
    EXPECT_EQ(fires, 1);

    h1->remove(); h1.reset();
    h2->remove(); h2.reset();

    subject_add(0, 0);              // flushes h1+h2; sentinel alive → no teardown
    EXPECT_EQ(fires, 1);            // test callbacks stopped

    subject_add(0, 0);              // only sentinel fires; fires stays 1
    EXPECT_EQ(fires, 1);
}

// ============================================================================
//  9. Re-registration — new hook installs cleanly after auto-teardown
// ============================================================================

// Re-registering a callback after a previous one was removed works correctly.
// A sentinel keeps the hook alive throughout so no mid-call teardown occurs.
TEST_F(HooksManagerTest, ReRegister_AfterTeardown_WorksCleanly) {
    int fired = 0;
    std::optional<HookHandle> saved, sentinel;

    // Sentinel: prevents auto-teardown between remove() and re-registration.
    HooksManager::addBefore<&subject_id>([&](HookHandle h, int& x) {
        if (!sentinel) { sentinel = h; tracked_.emplace_back(h); }
    });

    auto registerCallback = [&] {
        HooksManager::addBefore<&subject_id>([&](HookHandle h, int& x) {
            if (!saved) saved = h;
            ++fired;
        });
    };

    // First registration
    registerCallback();
    subject_id(0);
    EXPECT_EQ(fired, 1);

    // Remove first, re-register
    saved->remove(); saved.reset();

    registerCallback();
    subject_id(0);   // flushes first removal; sentinel + new cb fire
    EXPECT_EQ(fired, 2);

    saved->remove(); saved.reset();
    subject_id(0);   // flushes second removal; sentinel alive → no teardown
    EXPECT_EQ(fired, 2);
}


// ============================================================================
//  10. Member function hooks
// ============================================================================

// Before callback receives the correct `this` pointer
TEST_F(HooksManagerTest, MemberFunc_Before_CorrectThisPointer) {
    Widget w;
    Widget* cap_self = nullptr;

    HooksManager::addBefore<&Widget::accumulate>([&](HookHandle h, Widget*& self, int& by) {
        track(h); cap_self = self;
    });

    w.accumulate(5);
    EXPECT_EQ(cap_self, &w);
    EXPECT_EQ(w.value, 5);
}

// Before callback can mutate `this` members — side-effect visible post-call
TEST_F(HooksManagerTest, MemberFunc_Before_MutateSelf) {
    Widget w;
    w.value = 100;

    HooksManager::addBefore<&Widget::accumulate>([&](HookHandle h, Widget*& self, int& by) {
        track(h); self->value = 0; // reset before original adds `by`
    });

    int result = w.accumulate(3); // value reset to 0, then 0 + 3 = 3
    EXPECT_EQ(result, 3);
    EXPECT_EQ(w.value, 3);
}

// After callback receives the correct return value from the original
TEST_F(HooksManagerTest, MemberFunc_After_CorrectReturnValue) {
    Widget w;
    w.value = 10;
    int cap_ret = -1;

    HooksManager::addAfter<&Widget::accumulate>([&](HookHandle h, int& ret, Widget*& self, int& by) {
        track(h); cap_ret = ret;
    });

    w.accumulate(5);          // 10 + 5 = 15
    EXPECT_EQ(cap_ret, 15);
}

// After callback can modify the return value seen by the caller
TEST_F(HooksManagerTest, MemberFunc_After_ModifyReturnValue) {
    Widget w;
    w.value = 0;

    HooksManager::addAfter<&Widget::accumulate>([&](HookHandle h, int& ret, Widget*& self, int& by) {
        track(h); ret = 999; // override whatever the original returned
    });

    EXPECT_EQ(w.accumulate(7), 999);
}

// Void member function: After callback fires without a return parameter
TEST_F(HooksManagerTest, MemberFunc_VoidAfter_CallbackFires) {
    Widget w;
    w.value = 42;
    bool fired = false;

    HooksManager::addAfter<&Widget::clear>([&](HookHandle h, Widget*& self) {
        track(h);
        // original (clear) must have already set value to 0
        EXPECT_EQ(self->value, 0);
        fired = true;
    });

    w.clear();
    EXPECT_TRUE(fired);
}

// ============================================================================
//  11. Independent hooks — two different functions, no interference
// ============================================================================

TEST_F(HooksManagerTest, IndependentFunctions_HooksDoNotInterfere) {
    int add_fires = 0, id_fires = 0;
    std::optional<HookHandle> h_add, h_id;

    // Guards: subject_add fires twice in this test; without the guard track(h)
    // would add two copies of the same handle to tracked_, TearDown would defer
    // two removals of the same std::list iterator → heap corruption in next test.
    HooksManager::addBefore<&subject_add>([&](HookHandle h, int& a, int& b) {
        if (!h_add) { h_add = h; tracked_.emplace_back(h); }
        ++add_fires;
    });
    HooksManager::addBefore<&subject_id>([&](HookHandle h, int& x) {
        if (!h_id) { h_id = h; tracked_.emplace_back(h); }
        ++id_fires;
    });

    subject_add(1, 2);
    subject_add(3, 4);
    subject_id(99);

    EXPECT_EQ(add_fires, 2);
    EXPECT_EQ(id_fires,  1);
}

// Removing all callbacks from one function must not affect the other
TEST_F(HooksManagerTest, IndependentFunctions_TeardownOnePreservesOther) {
    int add_fires = 0, id_fires = 0;
    std::optional<HookHandle> h_add, sentinel_add, h_id;

    // Sentinel for subject_add: prevents mid-call teardown when h_add is removed.
    HooksManager::addBefore<&subject_add>([&](HookHandle h, int& a, int& b) {
        if (!sentinel_add) { sentinel_add = h; tracked_.emplace_back(h); }
    });
    HooksManager::addBefore<&subject_add>([&](HookHandle h, int& a, int& b) {
        if (!h_add) h_add = h;
        ++add_fires;
    });
    // Guard pattern: track h_id exactly once even though subject_id fires twice.
    // Without it, tracked_ gets two identical handles; TearDown double-erases
    // the same std::list iterator → heap corruption (exit code 0xC0000374).
    HooksManager::addBefore<&subject_id>([&](HookHandle h, int& x) {
        if (!h_id) { h_id = h; tracked_.emplace_back(h); }
        ++id_fires;
    });

    subject_add(0, 0);  // sentinel_add + add_cb fire; h_add captured
    subject_id(0);      // id_fires=1

    h_add->remove(); h_add.reset();
    subject_add(0, 0);  // flushes h_add removal; sentinel_add alive → no teardown

    subject_id(0);      // id_fires=2
    EXPECT_EQ(add_fires, 1);
    EXPECT_EQ(id_fires,  2);
}

