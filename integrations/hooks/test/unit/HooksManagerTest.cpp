// =============================================================================
//  HooksManagerTest.cpp
//
//  Coverage map (rows = hook type, columns = function shape):
//
//                    │ free  │ member  │ member  │ member const │ member const │ static │
//                    │       │ (nonconst)│ const trivial │ non-trivial │ void │        │
//    Before/After    │  X    │   X     │    X    │      X       │      -       │   X    │
//    Replace         │  X    │   -     │    -    │      X       │      -       │   -    │
//    Ignore (toggle) │  X    │   -     │    -    │      -       │      X       │   -    │
//    IgnoreCond.     │  X    │   -     │    -    │      X       │      -       │   -    │
//
//  (dashes are shapes already exercised by another row — the underlying
//  dispatch mechanism per function shape is what matters, not every
//  hook-type/shape cross product.)
//
//  Every test that registers a hook also removes it before the test ends
//  (either via HookHandle::remove() or a positional/manager-level remove
//  call) so tests don't leak detours into one another — HooksManager's hook
//  registry is process-global (static), not reset between tests.
// =============================================================================

#include <gtest/gtest.h>

#include "HooksManager.h"

#include <atomic>
#include <string>
#include <vector>

// noinline: keeps target functions from being inlined into their call sites,
// which would leave nothing at their address for the detour to patch.
#if defined(_MSC_VER)
#  define HOOKS_TEST_NOINLINE __declspec(noinline)
#else
#  define HOOKS_TEST_NOINLINE __attribute__((noinline))
#endif

// HOOKS_TEST_PAD: an x64 detour needs a handful of bytes of prologue to
// safely overwrite. A trivial one-liner like `return a + b;` can compile
// down to 3-4 bytes under optimization (e.g. RelWithDebInfo/Release) — too
// short to hook at all, so the install fails (loudly now — see
// HooksManager.h's install()) and the function would otherwise run
// untouched. An atomic increment can never be optimized away (it's a real,
// observable side effect) and reliably pads the compiled body past that
// threshold regardless of optimization level, without changing any test's
// observable behavior.
#define HOOKS_TEST_PAD() \
    do { static std::atomic<int> padCounter{0}; padCounter.fetch_add(1, std::memory_order_relaxed); } while (0)

namespace {

// ─────────────────────────── Free-function targets ───────────────────────────

HOOKS_TEST_NOINLINE int FreeAdd(int a, int b) {
    HOOKS_TEST_PAD();
    return a + b;
}

HOOKS_TEST_NOINLINE void FreeLog(std::vector<std::string> &sink, const std::string &msg) {
    sink.push_back(msg);
}

HOOKS_TEST_NOINLINE int FreeMultiBefore(int x) {
    HOOKS_TEST_PAD();
    return x;
}

HOOKS_TEST_NOINLINE int FreeMultiAfter(int x) {
    HOOKS_TEST_PAD();
    return x;
}

HOOKS_TEST_NOINLINE int FreeBeforeRemoveByHandle(int x) {
    HOOKS_TEST_PAD();
    return x;
}

HOOKS_TEST_NOINLINE int FreePositionBefore(int x) {
    HOOKS_TEST_PAD();
    return x;
}

HOOKS_TEST_NOINLINE int FreeNeverHooked(int x) {
    HOOKS_TEST_PAD();
    return x;
}

HOOKS_TEST_NOINLINE void FreeIgnoreTarget(bool &calledOriginal) {
    HOOKS_TEST_PAD();
    calledOriginal = true;
}

HOOKS_TEST_NOINLINE int FreeIgnoreConditionalTarget(int x) {
    HOOKS_TEST_PAD();
    return x + 100; // "real" work; skip should avoid this offset entirely
}

HOOKS_TEST_NOINLINE void FreeIgnoreConditionalVoidTarget(bool &ran, int flag) {
    HOOKS_TEST_PAD();
    ran = true;
}

HOOKS_TEST_NOINLINE int FreeIgnoreCondRemoveTarget(int x) {
    HOOKS_TEST_PAD();
    return x;
}

HOOKS_TEST_NOINLINE int FreeReplaceTarget(int x) {
    HOOKS_TEST_PAD();
    return x * 1000; // sentinel: if this runs, Replace failed to fully substitute
}

HOOKS_TEST_NOINLINE void FreeReplaceVoidTarget(bool &calledOriginal) {
    HOOKS_TEST_PAD();
    calledOriginal = true;
}

HOOKS_TEST_NOINLINE int FreeReplaceRemoveTarget(int x) {
    HOOKS_TEST_PAD();
    return x;
}

// ────────────────────────────── Member targets ────────────────────────────────
// Covers: non-const (with/without return), const trivial return, const
// non-trivial return, const void return, and a static member (which decays
// to a plain free function pointer, so it is covered by the free-function
// machinery too).
class Widget {
public:
    HOOKS_TEST_NOINLINE int add(int a, int b) {
        _calls++;
        return a + b;
    }

    HOOKS_TEST_NOINLINE void increment(int by) {
        HOOKS_TEST_PAD();
        _value += by;
    }

    HOOKS_TEST_NOINLINE int value() const {
        HOOKS_TEST_PAD();
        return _value;
    }

    HOOKS_TEST_NOINLINE std::string describe() const {
        return "Widget(" + std::to_string(_value) + ")";
    }

    HOOKS_TEST_NOINLINE void ping() const {
        HOOKS_TEST_PAD();
        _pings++;
    }

    HOOKS_TEST_NOINLINE static int square(int x) {
        HOOKS_TEST_PAD();
        return x * x;
    }

    int _value = 0;
    int _calls = 0;
    mutable int _pings = 0;
};

} // namespace

// =============================================================================
//  Before / After — free functions
// =============================================================================

TEST(HooksManagerTest, FreeFunction_BeforeMutatesArgs_AfterSeesAndMutatesResult) {
    std::vector<int> beforeSeen;
    std::vector<int> afterSeen;

    HooksManager::addBefore<&FreeAdd>([&](HookHandle, int &a, int &b) {
        beforeSeen.push_back(a + b);
        a += 10; // mutate before the original runs
    });
    HooksManager::addAfter<&FreeAdd>([&](HookHandle, int &result, int &a, int &b) {
        afterSeen.push_back(result);
        result += 1; // mutate the return value
    });

    const int result = FreeAdd(2, 3);

    EXPECT_EQ(beforeSeen, (std::vector<int>{5}));
    EXPECT_EQ(result, 16);              // (2+10) + 3, then +1 from After
    EXPECT_EQ(afterSeen, (std::vector<int>{15})); // what After observed before its own mutation

    HooksManager::removeBefore<&FreeAdd>(0);
    HooksManager::removeAfter<&FreeAdd>(0);
    EXPECT_EQ(FreeAdd(2, 3), 5); // fully unhooked, original behavior restored
}

TEST(HooksManagerTest, FreeFunction_VoidReturn_BeforeAndAfterBothRun) {
    std::vector<std::string> log;
    std::vector<std::string> seenInBefore;
    std::vector<std::string> seenInAfter;

    HooksManager::addBefore<&FreeLog>([&](HookHandle, std::vector<std::string> &, const std::string &msg) {
        seenInBefore.push_back(msg);
    });
    HooksManager::addAfter<&FreeLog>([&](HookHandle, std::vector<std::string> &, const std::string &msg) {
        seenInAfter.push_back(msg);
    });

    FreeLog(log, "hello");

    EXPECT_EQ(log, (std::vector<std::string>{"hello"}));
    EXPECT_EQ(seenInBefore, (std::vector<std::string>{"hello"}));
    EXPECT_EQ(seenInAfter, (std::vector<std::string>{"hello"}));

    HooksManager::removeBefore<&FreeLog>(0);
    HooksManager::removeAfter<&FreeLog>(0);
}

// =============================================================================
//  Before / After — multiple registrations, positional insert/remove, handle removal
// =============================================================================

TEST(HooksManagerTest, FreeFunction_MultipleBefore_OrderAndPositionalInsert) {
    std::vector<std::string> order;

    HooksManager::addBefore<&FreeMultiBefore>([&](HookHandle, int &) { order.push_back("first"); });
    HooksManager::addBefore<&FreeMultiBefore>([&](HookHandle, int &) { order.push_back("second"); });
    HooksManager::addBefore<&FreeMultiBefore>([&](HookHandle, int &) { order.push_back("inserted-front"); }, 0);
    HooksManager::addBefore<&FreeMultiBefore>([&](HookHandle, int &) { order.push_back("inserted-middle"); }, 1);

    FreeMultiBefore(1);

    EXPECT_EQ(order, (std::vector<std::string>{
        "inserted-front", "inserted-middle", "first", "second"
    }));

    // Positions shift left after each removal, so removing index 0 four times
    // clears the whole list.
    HooksManager::removeBefore<&FreeMultiBefore>(0);
    HooksManager::removeBefore<&FreeMultiBefore>(0);
    HooksManager::removeBefore<&FreeMultiBefore>(0);
    HooksManager::removeBefore<&FreeMultiBefore>(0);
}

TEST(HooksManagerTest, FreeFunction_MultipleAfter_OrderAndRemoveByPosition) {
    std::vector<std::string> order;

    HooksManager::addAfter<&FreeMultiAfter>([&](HookHandle, int &, int &) { order.push_back("a"); });
    HooksManager::addAfter<&FreeMultiAfter>([&](HookHandle, int &, int &) { order.push_back("b"); });
    HooksManager::addAfter<&FreeMultiAfter>([&](HookHandle, int &, int &) { order.push_back("c"); }, 1);

    FreeMultiAfter(1);
    EXPECT_EQ(order, (std::vector<std::string>{"a", "c", "b"}));

    HooksManager::removeAfter<&FreeMultiAfter>(1); // removes "c"
    order.clear();
    FreeMultiAfter(1);
    EXPECT_EQ(order, (std::vector<std::string>{"a", "b"}));

    HooksManager::removeAfter<&FreeMultiAfter>(0);
    HooksManager::removeAfter<&FreeMultiAfter>(0);
}

TEST(HooksManagerTest, FreeFunction_Before_RemoveViaHandle) {
    int callCount = 0;
    HooksManager::addBefore<&FreeBeforeRemoveByHandle>([&](HookHandle handle, int &) {
        callCount++;
        handle.remove(); // self-remove; deferred until the next hook invocation
    });

    FreeBeforeRemoveByHandle(1); // runs once, schedules its own removal
    FreeBeforeRemoveByHandle(2); // removal flushed at entry; callback does not run again

    EXPECT_EQ(callCount, 1);
}

TEST(HooksManagerTest, FreeFunction_RemoveBefore_OutOfRangePosition_IsNoOp) {
    int calls = 0;
    HooksManager::addBefore<&FreePositionBefore>([&](HookHandle, int &) { calls++; });

    HooksManager::removeBefore<&FreePositionBefore>(5); // out of range → no-op
    FreePositionBefore(1);
    EXPECT_EQ(calls, 1);

    HooksManager::removeBefore<&FreePositionBefore>(0);
}

TEST(HooksManagerTest, RemoveCallsOnNeverHookedFunction_AreNoOps) {
    EXPECT_NO_THROW(HooksManager::removeBefore<&FreeNeverHooked>(0));
    EXPECT_NO_THROW(HooksManager::removeAfter<&FreeNeverHooked>(0));
    EXPECT_NO_THROW(HooksManager::removeReplace<&FreeNeverHooked>());
    EXPECT_NO_THROW(HooksManager::removeIgnoreConditionally<&FreeNeverHooked>());
    EXPECT_EQ(FreeNeverHooked(9), 9);
}

// =============================================================================
//  Before / After — member functions (non-const, const, static)
// =============================================================================

TEST(HooksManagerTest, MemberFunction_NonConstVoid_BeforeMutatesArg) {
    Widget w;
    HooksManager::addBefore<&Widget::increment>([](HookHandle, Widget *&, int &by) {
        by *= 2; // double the increment before it's applied
    });

    w.increment(5);
    EXPECT_EQ(w._value, 10);

    HooksManager::removeBefore<&Widget::increment>(0);
    w.increment(5);
    EXPECT_EQ(w._value, 15); // unhooked: no more doubling
}

TEST(HooksManagerTest, MemberFunction_NonConstNonVoid_AfterSeesResultAndSelf) {
    Widget w;
    std::vector<int> afterSeen;

    HooksManager::addAfter<&Widget::add>([&](HookHandle, int &result, Widget *&self, int &, int &) {
        afterSeen.push_back(result);
        EXPECT_EQ(self, &w);
        result *= 10;
    });

    EXPECT_EQ(w.add(2, 3), 50);
    EXPECT_EQ(afterSeen, (std::vector<int>{5}));
    EXPECT_EQ(w._calls, 1); // original body did run (side effect visible)

    HooksManager::removeAfter<&Widget::add>(0);
}

TEST(HooksManagerTest, MemberFunction_ConstTrivialReturn_AfterMutatesResult) {
    Widget w;
    w._value = 3;
    std::vector<int> afterSeen;

    HooksManager::addAfter<&Widget::value>([&](HookHandle, int &result, const Widget *&self) {
        afterSeen.push_back(result);
        EXPECT_EQ(self, &w);
        result += 100;
    });

    EXPECT_EQ(w.value(), 103);
    EXPECT_EQ(afterSeen, (std::vector<int>{3}));

    HooksManager::removeAfter<&Widget::value>(0);
}

// A const method returning a non-trivial type (std::string) — dispatched
// through the exact same by-value mechanism as any other return type; the
// compiler decides the actual calling convention (register vs hidden
// pointer), not this code, so there's nothing special for Before/After here.
TEST(HooksManagerTest, MemberFunction_ConstNonTrivialReturn_BeforeAndAfter) {
    Widget w;
    w._value = 42;
    std::vector<int> beforeSeenValue;
    std::vector<std::string> afterSeenResult;

    HooksManager::addBefore<&Widget::describe>([&](HookHandle, const Widget *&self) {
        // Read state via self rather than calling self->describe() again,
        // which would recursively re-enter the hook.
        beforeSeenValue.push_back(self->_value);
    });
    HooksManager::addAfter<&Widget::describe>([&](HookHandle, std::string &result, const Widget *&) {
        afterSeenResult.push_back(result);
        result += "!";
    });

    const std::string result = w.describe();

    EXPECT_EQ(beforeSeenValue, (std::vector<int>{42}));
    EXPECT_EQ(afterSeenResult, (std::vector<std::string>{"Widget(42)"}));
    EXPECT_EQ(result, "Widget(42)!");

    HooksManager::removeBefore<&Widget::describe>(0);
    HooksManager::removeAfter<&Widget::describe>(0);
    EXPECT_EQ(w.describe(), "Widget(42)"); // fully unhooked
}

TEST(HooksManagerTest, StaticMemberFunction_BeforeAndAfter) {
    // Widget::square is static, so &Widget::square decays to a plain
    // R(*)(Args...) — it is dispatched through the free-function machinery.
    std::vector<int> beforeSeen, afterSeen;

    HooksManager::addBefore<&Widget::square>([&](HookHandle, int &x) { beforeSeen.push_back(x); });
    HooksManager::addAfter<&Widget::square>([&](HookHandle, int &result, int &) { afterSeen.push_back(result); });

    EXPECT_EQ(Widget::square(6), 36);
    EXPECT_EQ(beforeSeen, (std::vector<int>{6}));
    EXPECT_EQ(afterSeen, (std::vector<int>{36}));

    HooksManager::removeBefore<&Widget::square>(0);
    HooksManager::removeAfter<&Widget::square>(0);
}

// =============================================================================
//  Ignore — void-only toggle, single instance, activate/deactivate/reactivate
// =============================================================================

TEST(HooksManagerTest, Ignore_FreeVoidFunction_ActivateDeactivateReactivate) {
    bool called = false;

    HooksManager::addIgnore<&FreeIgnoreTarget>();
    FreeIgnoreTarget(called);
    EXPECT_FALSE(called); // original skipped while Ignore is active

    HooksManager::removeIgnore<&FreeIgnoreTarget>();
    FreeIgnoreTarget(called);
    EXPECT_TRUE(called); // deactivated: original runs again

    called = false;
    HooksManager::addIgnore<&FreeIgnoreTarget>(); // reactivate
    FreeIgnoreTarget(called);
    EXPECT_FALSE(called);

    HooksManager::removeIgnore<&FreeIgnoreTarget>();
}

// Const void methods and const non-trivial-return methods take different
// paths internally (register return vs hidden pointer return, decided by
// the compiler) — this exercises the void one specifically.
TEST(HooksManagerTest, Ignore_MemberConstVoid_ActivateDeactivate) {
    Widget w;

    HooksManager::addIgnore<&Widget::ping>();
    w.ping();
    w.ping();
    EXPECT_EQ(w._pings, 0); // original skipped both times

    HooksManager::removeIgnore<&Widget::ping>();
    w.ping();
    EXPECT_EQ(w._pings, 1); // reactivated: original runs
}

// Note: HooksManager::addIgnore<&Widget::describe> would not compile —
// VoidHookableFunction<F> rejects non-void-returning functions at compile
// time, which is the point of the "void functions only" requirement.

// =============================================================================
//  IgnoreConditionally — single instance, decides per call, any return type
// =============================================================================

TEST(HooksManagerTest, IgnoreConditionally_FreeFunctionNonVoid_SkipsWithSubstituteResult) {
    HooksManager::addIgnoreConditionally<&FreeIgnoreConditionalTarget>(
        [](HookHandle, bool &ignore, int &result, int &x) {
            if (x < 0) {
                ignore = true;
                result = 0; // substitute for negative input
            }
        });

    EXPECT_EQ(FreeIgnoreConditionalTarget(5), 105);  // original ran
    EXPECT_EQ(FreeIgnoreConditionalTarget(-5), 0);   // skipped, substitute used

    HooksManager::removeIgnoreConditionally<&FreeIgnoreConditionalTarget>();
    EXPECT_EQ(FreeIgnoreConditionalTarget(-5), 95);  // unhooked: real behavior
}

TEST(HooksManagerTest, IgnoreConditionally_FreeFunctionVoid_SkipsBasedOnArg) {
    HooksManager::addIgnoreConditionally<&FreeIgnoreConditionalVoidTarget>(
        [](HookHandle, bool &ignore, bool &, int &flag) {
            if (flag == 0) ignore = true;
        });

    bool ran = false;
    FreeIgnoreConditionalVoidTarget(ran, 0);
    EXPECT_FALSE(ran); // skipped

    FreeIgnoreConditionalVoidTarget(ran, 1);
    EXPECT_TRUE(ran); // not skipped

    HooksManager::removeIgnoreConditionally<&FreeIgnoreConditionalVoidTarget>();
}

TEST(HooksManagerTest, IgnoreConditionally_RemoveViaHandle) {
    int callbackCalls = 0;
    HooksManager::addIgnoreConditionally<&FreeIgnoreCondRemoveTarget>(
        [&](HookHandle handle, bool &, int &, int &) {
            callbackCalls++;
            handle.remove();
        });

    FreeIgnoreCondRemoveTarget(1); // callback runs once, self-removes (deferred)
    FreeIgnoreCondRemoveTarget(2); // pending removal flushed; callback doesn't run again

    EXPECT_EQ(callbackCalls, 1);
}

// Unlike the simple Ignore toggle, IgnoreConditionally is not void-restricted,
// so it's also valid for const methods with non-trivial return types.
TEST(HooksManagerTest, IgnoreConditionally_MemberConstNonTrivialReturn_SkipsAndSuppliesResult) {
    Widget w;
    w._value = 7;
    bool skip = true;

    HooksManager::addIgnoreConditionally<&Widget::describe>(
        [&](HookHandle, bool &ignore, std::string &result, const Widget *&) {
            ignore = skip;
            if (skip) result = "skipped";
        });

    EXPECT_EQ(w.describe(), "skipped");

    skip = false;
    EXPECT_EQ(w.describe(), "Widget(7)");

    HooksManager::removeIgnoreConditionally<&Widget::describe>();
    EXPECT_EQ(w.describe(), "Widget(7)");
}

// =============================================================================
//  Replace — single instance, fully substitutes the original, own HookHandle
// =============================================================================

TEST(HooksManagerTest, Replace_FreeFunctionNonVoid_FullySubstitutesOriginal) {
    std::vector<int> beforeSeen, afterSeen;

    HooksManager::addBefore<&FreeReplaceTarget>([&](HookHandle, int &x) { beforeSeen.push_back(x); });
    HooksManager::addReplace<&FreeReplaceTarget>([](HookHandle, int &x) -> int {
        return x + 1; // nothing like the original's x*1000
    });
    HooksManager::addAfter<&FreeReplaceTarget>([&](HookHandle, int &result, int &) { afterSeen.push_back(result); });

    const int result = FreeReplaceTarget(4);

    EXPECT_EQ(result, 5);                          // Replace's result, not the original's
    EXPECT_EQ(beforeSeen, (std::vector<int>{4}));  // Before still runs around Replace
    EXPECT_EQ(afterSeen, (std::vector<int>{5}));   // After sees Replace's result

    HooksManager::removeReplace<&FreeReplaceTarget>();
    HooksManager::removeBefore<&FreeReplaceTarget>(0);
    HooksManager::removeAfter<&FreeReplaceTarget>(0);

    EXPECT_EQ(FreeReplaceTarget(4), 4000); // fully unhooked: real original runs
}

TEST(HooksManagerTest, Replace_FreeFunctionVoid_OriginalBodyNeverRuns) {
    bool calledOriginal = false;
    bool calledReplacement = false;

    HooksManager::addReplace<&FreeReplaceVoidTarget>([&](HookHandle, bool &) {
        calledReplacement = true;
        // deliberately not touching the flag, to prove the original body
        // (which would set it) never ran
    });

    FreeReplaceVoidTarget(calledOriginal);

    EXPECT_TRUE(calledReplacement);
    EXPECT_FALSE(calledOriginal);

    HooksManager::removeReplace<&FreeReplaceVoidTarget>();
}

// Replace on a const method with a non-trivial return type — same by-value
// Replace signature as everywhere else; no special handling needed.
TEST(HooksManagerTest, Replace_MemberConstNonTrivialReturn_FullySubstitutesOriginal) {
    Widget w;
    w._value = 9;

    HooksManager::addReplace<&Widget::describe>([](HookHandle, const Widget *&self) -> std::string {
        return "replaced:" + std::to_string(self->_value);
    });

    EXPECT_EQ(w.describe(), "replaced:9");

    HooksManager::removeReplace<&Widget::describe>();
    EXPECT_EQ(w.describe(), "Widget(9)"); // unhooked: real original runs
}

TEST(HooksManagerTest, Replace_RemoveViaHandle) {
    int replacementCalls = 0;
    HooksManager::addReplace<&FreeReplaceRemoveTarget>([&](HookHandle handle, int &) -> int {
        replacementCalls++;
        handle.remove(); // self-remove; deferred until the next hook invocation
        return -1;
    });

    EXPECT_EQ(FreeReplaceRemoveTarget(3), -1); // replaced once, self-removes
    EXPECT_EQ(FreeReplaceRemoveTarget(3), 3);  // removal flushed; original restored

    EXPECT_EQ(replacementCalls, 1);
}

TEST(HooksManagerTest, Replace_RegisteringAgainOverwritesPreviousSingleton) {
    HooksManager::addReplace<&FreeReplaceTarget>([](HookHandle, int &x) -> int { return x + 1; });
    HooksManager::addReplace<&FreeReplaceTarget>([](HookHandle, int &x) -> int { return x + 2; });

    // Only one Replace can exist per function — the second registration wins.
    EXPECT_EQ(FreeReplaceTarget(10), 12);

    HooksManager::removeReplace<&FreeReplaceTarget>();
    EXPECT_EQ(FreeReplaceTarget(10), 10000); // unhooked: real original runs
}
