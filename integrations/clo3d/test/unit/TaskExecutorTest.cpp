#include <gtest/gtest.h>

#include <cmath>
#include <atomic>
#include <memory>
#include <cstddef>

#include "Task.h"
#include "BaseTask.h"
#include "TaskGroup.h"
#include "TaskExecutor.h"

using namespace CLO3D;

namespace {
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
}