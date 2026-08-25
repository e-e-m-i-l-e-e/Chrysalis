#include <gtest/gtest.h>

#include "Pattern.h"
#include "Project.h"
#include "Parameter.h"
#include "ProjectSpace.h"

#include "CallTracker.h"
#include "mocks/InstructionsContainerMock.h"

using namespace Chrysalis;

class ProjectThreadTest: public ::testing::Test {
protected:
    void SetUp() override {
        instructions_ = new InstructionsContainerMock();
        project_ = std::make_unique<Project>("Untitled",
                                             std::make_unique<ProjectSpace>(),
                                             std::make_unique<PatternsContainer>(),
                                             std::make_unique<ParametersContainer>(),
                                             std::make_unique<OptionsContainerMock>(),
                                             std::make_unique<ExpressionsContainerMock>(),
                                             std::unique_ptr<InstructionsContainerMock>(instructions_));
    }
    CallTracker callTracker_;
    std::unique_ptr<Project> project_;
    InstructionsContainerMock* instructions_;
    
    static inline auto TIMEOUT = std::chrono::milliseconds(2000);
};

TEST_F(ProjectThreadTest, Instructions_are_executed_asynchronously) {
    using ::testing::Invoke;

    EXPECT_CALL(*instructions_, execute()).WillOnce(Invoke([&] -> void {
        ++callTracker_;
    }));
    EXPECT_CALL(*instructions_, ignore()).Times(1);

    project_->execute();

    ASSERT_TRUE(callTracker_.wait(1, TIMEOUT)) << "instructions_->execute() was not invoked within the timeout";
}

// TODO: Execute_can_be_called_multiple_times
// TEST_F(ProjectThreadTest, Execute_can_be_called_multiple_times) {
//     using ::testing::Invoke;
//     EXPECT_CALL(*instructions_, execute()).Times(2).WillRepeatedly(Invoke([&] {
//         ++callTracker_;
//     }));
//     EXPECT_CALL(*instructions_, ignore()).Times(1);
//
//     project_->execute();
//     ASSERT_TRUE(callTracker_.wait(1, TIMEOUT));
//     project_->execute();
//     ASSERT_TRUE(callTracker_.wait(2, TIMEOUT));
// }

TEST_F(ProjectThreadTest, Concurrent_execute_calls) {
    using ::testing::Invoke;
    constexpr size_t NUMBER_OF_CONCURRENT_CALLS = 50;

    EXPECT_CALL(*instructions_, execute()).WillRepeatedly(Invoke([&] {
        ++callTracker_;
    }));
    EXPECT_CALL(*instructions_, ignore()).Times(1);
    
    std::vector<std::thread> callers;
    callers.reserve(NUMBER_OF_CONCURRENT_CALLS);
    for (size_t i = 0; i < NUMBER_OF_CONCURRENT_CALLS; ++i) {
        callers.emplace_back([&] {
            project_->execute();
        });
    }
    for (auto& t: callers) t.join();

    ASSERT_TRUE(callTracker_.wait(1, TIMEOUT));
}

TEST_F(ProjectThreadTest, Run_queued_task_in_execution_thread) {
    EXPECT_CALL(*instructions_, ignore()).Times(1);
    EXPECT_CALL(*instructions_, execute()).Times(0);

    project_->onExecuted([&] {
        ++callTracker_;
    });

    ASSERT_TRUE(callTracker_.wait(1, TIMEOUT)) << "Queued task never ran.";
}

TEST_F(ProjectThreadTest, Tasks_are_scheduled_concurrently) {
    constexpr size_t NUMBER_OF_PRODUCERS = 8;
    constexpr size_t NUMBER_OF_TASKS = 25;

    EXPECT_CALL(*instructions_, ignore()).Times(1);
    EXPECT_CALL(*instructions_, execute()).Times(0);

    std::atomic count = 0;

    std::vector<std::thread> producers;
    producers.reserve(NUMBER_OF_PRODUCERS);
    for (size_t p = 0; p < NUMBER_OF_PRODUCERS; ++p) {
        producers.emplace_back([&] -> void {
            for (size_t i = 0; i < NUMBER_OF_TASKS; ++i) {
                project_->onExecuted([&] -> void {
                    count.fetch_add(1, std::memory_order_relaxed);
                    ++callTracker_;
                });
            }
        });
    }
    for (auto& t: producers) t.join();

    ASSERT_TRUE(callTracker_.wait(NUMBER_OF_PRODUCERS * NUMBER_OF_TASKS, TIMEOUT));
    EXPECT_EQ(count.load(), NUMBER_OF_PRODUCERS * NUMBER_OF_TASKS);
}

TEST_F(ProjectThreadTest, ReentrantOnExecutedFromInsideInstructionsExecuteDoesNotDeadlock) {
    using ::testing::Invoke;

    EXPECT_CALL(*instructions_, execute()).WillOnce(Invoke([&] {
        project_->onExecuted([&] {
            ++callTracker_;
        });
    }));
    EXPECT_CALL(*instructions_, ignore()).Times(1);

    project_->execute();

    ASSERT_TRUE(callTracker_.wait(1, TIMEOUT)) << "reentrant onExecuted() call deadlocked or was never processed";
}

TEST_F(ProjectThreadTest, Destructor_ignores_queued_tasks) {
    using ::testing::AtLeast;

    EXPECT_CALL(*instructions_, ignore()).Times(1);
    EXPECT_CALL(*instructions_, execute()).Times(AtLeast(0));

    for (int i = 0; i < 100; ++i) {
        project_->onExecuted([] {});
    }
    project_->execute();
    project_.reset();
    SUCCEED();
}