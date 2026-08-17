#include <gtest/gtest.h>

#include <atomic>
#include <chrono>
#include <memory>
#include <thread>

#include <QCoreApplication>
#include <QThreadPool>

#include "Task.h"
#include "TaskExecutor.h"

#include "Logging.h"
#define LOGGER_NAME "TaskExecutorTest"
#include "TaskGroup.h"

using namespace CLO3D;

namespace {

// Restores the global QThreadPool's max thread count on scope exit, so this
// test's deliberate constraint can never leak into other tests sharing the
// same process/global pool.
class ScopedMaxThreadCount {
public:
    explicit ScopedMaxThreadCount(const int count)
        : original_(QThreadPool::globalInstance()->maxThreadCount()) {
        QThreadPool::globalInstance()->setMaxThreadCount(count);
    }
    ~ScopedMaxThreadCount() {
        QThreadPool::globalInstance()->setMaxThreadCount(original_);
    }
private:
    int original_;
};

}  // namespace

// TaskGroup::run() (protected - only reachable via TaskExecutor, exactly as
// intended) submits its own coordinating lambda to the global thread pool,
// then blocks *inside that lambda* waiting on each sub-task's future - and
// each sub-task is submitted to the SAME global pool. If the pool is
// exhausted, the group's own lambda can occupy the only available worker
// while waiting for sub-tasks that need a worker slot to even start,
// starving them out.
//
// This test goes through TaskExecutor::submit() - the only public entry
// point - rather than calling TaskGroup::run() directly, and deliberately
// constrains the pool to a single worker (fewer workers than the group has
// sub-tasks) to make that scenario reproducible.
//
// SAFETY: this test must never be capable of hanging the test binary, even
// if the deadlock it's checking for genuinely reproduces. completed and
// runCount are heap-allocated and kept alive via shared_ptr so a stray late
// callback can't touch a destroyed stack frame, and the assertion is a
// bounded poll rather than a blocking wait.
TEST(TaskExecutorTest, TaskGroupDoesNotDeadlockWhenThreadPoolIsExhausted) {
    const ScopedMaxThreadCount constrainedPool(4);

    TaskExecutor executor;
    auto group = std::make_unique<TaskGroup>("StarvationProbe");
    constexpr int TASK_COUNT = 100;  // more tasks than available worker threads
    const auto runCount = std::make_shared<std::atomic<int>>(0);

    for (int i = 0; i < TASK_COUNT; ++i) {
        group->addTask(std::make_unique<Task>(QString("SubTask%1").arg(i), [runCount] -> void {
            ++(*runCount);
        }));
    }

    const auto completed = std::make_shared<std::atomic<bool>>(false);
    executor.submit(std::move(group), [completed] -> void {
        *completed = true;
    });

    constexpr auto TIMEOUT = std::chrono::seconds(5);
    const auto deadline = std::chrono::steady_clock::now() + TIMEOUT;
    while (!*completed && std::chrono::steady_clock::now() < deadline) {
        // QFutureWatcher::finished is delivered via a queued connection back
        // to this thread's Qt event loop - without pumping it here, the
        // callback would never fire and this test would time out regardless
        // of whether the deadlock it's checking for is actually present.
        QCoreApplication::processEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }

    EXPECT_TRUE(*completed)
        << "TaskExecutor::submit(TaskGroup) did not complete within " << TIMEOUT.count()
        << "s under a single-worker thread pool with " << TASK_COUNT
        << " sub-tasks. This suggests TaskGroup's own blocking-wait lambda "
        << "is starving its sub-tasks of worker threads from the same pool "
        << "(see TaskGroup::run()) rather than a slow environment.";
}

namespace {
    // Builds a tree of nested TaskGroups: `depth` levels deep, `breadth`
    // children per group, with a leaf Task (incrementing runCount) at the
    // bottom of every branch. depth=0 returns a single leaf Task directly.
    std::unique_ptr<BaseTask> buildNestedTask(const int depth, const int breadth,
                                               const std::shared_ptr<std::atomic<int>>& runCount,
                                               const QString& namePrefix) {
        if (depth == 0) {
            return std::make_unique<Task>(namePrefix, [runCount] { ++(*runCount); });
        }
        auto group = std::make_unique<TaskGroup>(namePrefix);
        for (int i = 0; i < breadth; ++i) {
            group->addTask(buildNestedTask(depth - 1, breadth, runCount,
                                            QString("%1.%2").arg(namePrefix).arg(i)));
        }
        return group;
    }

    // Submits `task` via executor and blocks (safely, with a bounded poll and
    // event-loop pumping) until either onSuccess fires or timeoutSeconds
    // elapses. Returns true if it completed in time.
    bool submitAndWait(TaskExecutor& executor, std::unique_ptr<BaseTask> task, const int timeoutSeconds) {
        const auto completed = std::make_shared<std::atomic<bool>>(false);
        executor.submit(std::move(task), [completed] { *completed = true; });

        const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(timeoutSeconds);
        while (!*completed && std::chrono::steady_clock::now() < deadline) {
            QCoreApplication::processEvents();
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
        return *completed;
    }
}  // namespace

// Wide + moderately deep: 3 levels of TaskGroup nesting, 3 children per
// level (39 leaf tasks total: 3 + 9 + 27... actually 3^3 = 27 leaves under
// the outermost group's 3 direct children, each themselves a 2-level tree).
// Single-worker pool, same starvation setup as the flat case above, but with
// every leaf reached through multiple layers of blocking TaskGroup::run()
// calls instead of one.
TEST(TaskExecutorTest, NestedTaskGroupsDoNotDeadlockWhenThreadPoolIsExhausted) {
    const ScopedMaxThreadCount constrainedPool(3);
    TaskExecutor executor;

    constexpr int DEPTH = 5;
    constexpr int BREADTH = 5;
    const auto runCount = std::make_shared<std::atomic<int>>(0);
    auto tree = buildNestedTask(DEPTH, BREADTH, runCount, "Nested");

    const bool completed = submitAndWait(executor, std::move(tree), 10);

    EXPECT_TRUE(completed)
        << "Nested TaskGroups (depth=" << DEPTH << ", breadth=" << BREADTH
        << ") did not complete within 10s under a single-worker thread pool. "
        << "Each nesting level adds another layer of blocking TaskGroup::run(), "
        << "which increases contention for the same starved pool.";

    if (completed) {
        int expectedLeaves = 1;
        for (int i = 0; i < DEPTH; ++i) expectedLeaves *= BREADTH;
        EXPECT_EQ(runCount->load(), expectedLeaves);
    }
}

// Deep, narrow chain: 10 levels of single-child TaskGroup nesting under a
// single-worker pool. Unlike the wide case, this maximizes the number of
// SIMULTANEOUSLY blocked TaskGroup::run() lambdas stacked on top of each
// other (each level's group blocks waiting on the next level down), which is
// the more direct stress test for any limit in whatever cooperative
// scheduling let the flatter cases above succeed.
TEST(TaskExecutorTest, DeeplyNestedTaskGroupsDoNotDeadlockWhenThreadPoolIsExhausted) {
    const ScopedMaxThreadCount constrainedPool(3);
    TaskExecutor executor;

    constexpr int DEPTH = 10;
    const auto runCount = std::make_shared<std::atomic<int>>(0);
    auto chain = buildNestedTask(DEPTH, 3, runCount, "Chain");

    const bool completed = submitAndWait(executor, std::move(chain), 15);

    EXPECT_TRUE(completed)
        << "A " << DEPTH << "-level-deep chain of nested TaskGroups did not "
        << "complete within 15s under a single-worker thread pool - "
        << DEPTH << " simultaneously blocked TaskGroup::run() lambdas were "
        << "not able to resolve.";

    if (completed) {
        EXPECT_EQ(runCount->load(), 1);
    }
}
