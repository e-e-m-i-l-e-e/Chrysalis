#include "TaskGroup.h"

#include <atomic>
#include <memory>

using namespace CLO3D;

TaskGroup::TaskGroup(const QString& name): BaseTask(name) {}

void TaskGroup::run(const std::function<void()>& onSuccess) {
    const auto remaining = std::make_shared<std::atomic<size_t>>(tasks_.size());
    for (const auto& task : tasks_) {
        task->run([&, remaining, onSuccess] -> void {
            if (remaining->fetch_sub(1) == 1) {
                onSuccess();
            }
        });
    }
}

void TaskGroup::addTask(std::unique_ptr<BaseTask> task) {
    tasks_.push_back(std::move(task));
}
