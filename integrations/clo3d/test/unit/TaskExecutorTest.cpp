#include <gtest/gtest.h>

#include <QEventLoop>

#include <cmath>
#include <atomic>
#include <memory>
#include <thread>
#include <vector>
#include <cstddef>

#include "Task.h"
#include "BaseTask.h"
#include "TaskGroup.h"
#include "TaskExecutor.h"

#include <QCoreApplication>

using namespace CLO3D;

namespace {

    const QString TASK_NAME = "Task";
    constexpr auto GROUP_NAME = "Group";

    TEST(TaskExecutorTest, All_tasks_are_executed) {
        constexpr size_t DEPTH = 5;
        constexpr size_t BREADTH = 5;

        size_t id = 0;
        std::atomic<size_t> successCount;
        auto createTask = [&](auto& self, const size_t depth) -> std::unique_ptr<BaseTask> {
            if (depth == 0) return std::make_unique<Task>(QString::number(id++), [&] -> void {
                ++successCount;
            });
            auto group = std::make_unique<TaskGroup>(QString::number(id++));
            for (size_t i = 0; i < BREADTH; ++i) {
                group->addTask(self(self, depth - 1));
            }
            return group;
        };
        TaskExecutor executor;
        executor.submit(createTask(createTask, DEPTH));
        EXPECT_EQ(successCount.load(), std::pow(BREADTH, DEPTH));
    }
    TEST(TaskExecutorTest, Exceptions_are_propagated) {
        auto group = std::make_unique<TaskGroup>(GROUP_NAME);
        group->addTask(std::make_unique<Task>("1", [&] -> void {}));
        group->addTask(std::make_unique<Task>("2", [] -> void {
            throw std::exception();
        }));
        TaskExecutor executor;
        EXPECT_THROW(executor.submit(std::move(group)), BaseTaskException);
    }
    TEST(TaskExecutorTest, Submit_blocking_group_with_no_exceptions_does_not_throw) {
        auto group = std::make_unique<TaskGroup>(GROUP_NAME);
        for (size_t i = 0; i < 5; ++i) {
            group->addTask(std::make_unique<Task>(QString::number(i), [] -> void {}));
        }
        TaskExecutor executor;
        EXPECT_NO_THROW(executor.submit(std::move(group)));
    }
    TEST(TaskExecutorTest, Submit_blocking_throws_for_single_failing_task) {
        TaskExecutor executor;
        EXPECT_THROW(
            executor.submit(std::make_unique<Task>("SingleFail", [] -> void {
                throw std::runtime_error("fail");
            })),
            BaseTaskException
        );
    }
    TEST(TaskExecutorTest, Submit_blocking_does_not_throw_for_single_successful_task) {
        TaskExecutor executor;
        bool executed = false;
        EXPECT_NO_THROW(executor.submit(std::make_unique<Task>("SingleSuccess", [&] -> void {
            executed = true;
        })));
        EXPECT_TRUE(executed);
    }
    TEST(TaskExecutorTest, Wait_for_unknown_task_does_not_throw) {
        TaskExecutor executor;
        EXPECT_NO_THROW(executor.wait("NonExistentTask"));
    }
    TEST(TaskExecutorTest, Wait_by_name_targets_correct_task_among_multiple) {
        TaskExecutor executor;
        int counter = 0;

        executor.submit(std::make_unique<Task>("A", [&] -> void {
            ++counter;
        }), [] -> void {}, [](const BaseTaskException&) -> void {});
        executor.submit(std::make_unique<Task>("B", [] -> void {
            throw std::runtime_error("fail B");
        }), [] -> void {}, [](const BaseTaskException&) -> void {});

        EXPECT_NO_THROW(executor.wait("A"));
        EXPECT_EQ(counter, 1);

        EXPECT_THROW(executor.wait("B"), BaseTaskException);
    }
    TEST(TaskExecutorTest, Async_submit_invokes_onSuccess_and_not_onException) {
        TaskExecutor executor;
        bool successCalled = false;
        bool exceptionCalled = false;

        executor.submit(
            std::make_unique<Task>(TASK_NAME, [] -> void {}),
            [&] -> void {
                successCalled = true;
            },
            [&](const BaseTaskException&) -> void {
                exceptionCalled = true;
            }
        );
        executor.wait(TASK_NAME);

        EXPECT_TRUE(successCalled);
        EXPECT_FALSE(exceptionCalled);
    }
    TEST(TaskExecutorTest, Async_submit_invokes_onException_and_not_onSuccess) {
        TaskExecutor executor;
        bool successCalled = false;
        bool exceptionCalled = false;

        executor.submit(
            std::make_unique<Task>(TASK_NAME, [] -> void {
                throw std::exception();
            }),
            [&] -> void {
                successCalled = true;
            },
            [&](const BaseTaskException&) -> void {
                exceptionCalled = true;
            }
        );
        EXPECT_THROW(executor.wait(TASK_NAME), BaseTaskException);

        EXPECT_FALSE(successCalled);
        EXPECT_TRUE(exceptionCalled);
    }
    TEST(TaskExecutorTest, Submit_with_default_onException_still_surfaces_exception_via_wait) {
        TaskExecutor executor;
        bool successCalled = false;

        executor.submit(
            std::make_unique<Task>(TASK_NAME, [] -> void {
                throw std::exception();
            }),
            [&] -> void {
                successCalled = true;
            }
        );

        EXPECT_THROW(executor.wait(TASK_NAME), BaseTaskException);
        EXPECT_FALSE(successCalled);
    }
    TEST(TaskExecutorTest, Async_submit_of_task_group_invokes_onSuccess_once_after_all_subtasks_complete) {
        TaskExecutor executor;
        constexpr size_t TASK_COUNT = 10;

        auto group = std::make_unique<TaskGroup>(GROUP_NAME);
        std::atomic<size_t> ranCount{0};
        for (size_t i = 0; i < TASK_COUNT; ++i) {
            group->addTask(std::make_unique<Task>(QString::number(i), [&] -> void { ++ranCount; }));
        }

        std::atomic<size_t> successCallCount{0};
        executor.submit(std::move(group), [&] -> void {
                             ++successCallCount;
                         }, [](const BaseTaskException&) -> void {});

        executor.wait(GROUP_NAME);

        EXPECT_EQ(ranCount.load(), TASK_COUNT);
        EXPECT_EQ(successCallCount.load(), 1u);
    }
    TEST(TaskExecutorTest, Async_submit_of_task_group_invokes_onException_once_when_any_subtask_fails) {
        TaskExecutor executor;
        constexpr size_t SUCCESS_COUNT = 4;
        constexpr size_t FAILURE_COUNT = 3;

        auto group = std::make_unique<TaskGroup>(GROUP_NAME);
        for (size_t i = 0; i < SUCCESS_COUNT; ++i) {
            group->addTask(std::make_unique<Task>(QString("S%1").arg(i), [] -> void {}));
        }
        for (size_t i = 0; i < FAILURE_COUNT; ++i) {
            group->addTask(std::make_unique<Task>(QString("F%1").arg(i), [] -> void {
                throw std::exception();
            }));
        }

        std::atomic<size_t> successCallCount{0};
        std::atomic<size_t> exceptionCallCount{0};
        executor.submit(std::move(group), [&] -> void {
                             ++successCallCount;
                         }, [&](const BaseTaskException&) -> void {
                             ++exceptionCallCount;
                         });

        EXPECT_THROW(executor.wait(GROUP_NAME), BaseTaskException);

        EXPECT_EQ(successCallCount.load(), 0u);
        EXPECT_EQ(exceptionCallCount.load(), 1u);
    }
    TEST(TaskExecutorTest, Concurrent_submissions_from_multiple_threads_are_all_tracked) {
        constexpr size_t THREAD_COUNT = 8;
        TaskExecutor executor;
        std::atomic<size_t> successCount{0};

        std::vector<std::thread> threads;
        threads.reserve(THREAD_COUNT);
        for (size_t i = 0; i < THREAD_COUNT; ++i) {
            threads.emplace_back([&, i] -> void {
                executor.submit(std::make_unique<Task>(QString("Thread%1").arg(i), [&] -> void {
                    ++successCount;
                }));
            });
        }
        for (auto& t: threads) t.join();

        EXPECT_EQ(successCount.load(), THREAD_COUNT);
        for (size_t i = 0; i < THREAD_COUNT; ++i) {
            EXPECT_NO_THROW(executor.wait(QString("Thread%1").arg(i)));
        }
    }
    TEST(TaskExecutorTest, Executor_destruction_waits_for_outstanding_tasks) {
        bool executed = false;
        {
            TaskExecutor executor;
            executor.submit(std::make_unique<Task>("Outstanding", [&] -> void {
                                 executed = true;
                             }), [] -> void {}, [](const BaseTaskException&) -> void {});
        }
        EXPECT_TRUE(executed);
    }

}