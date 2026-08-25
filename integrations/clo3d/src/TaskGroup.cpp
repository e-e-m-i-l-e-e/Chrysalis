#include "TaskGroup.h"

#include "TaskGroupException.h"

#include <atomic>
#include <memory>

using namespace CLO3D;

TaskGroup::TaskGroup(const QString& name): BaseTask(name) {}

void TaskGroup::wait() {
    TaskGroupException groupException(name());
    for (const auto& task : tasks_) {
        try {
            task->wait();
        } catch (const BaseTaskException& e) {
            groupException.addException(e);
        }
    }
    if (!groupException.empty()) throw groupException;
}

void TaskGroup::run(const std::function<void()>& onSuccess, const std::function<void(const BaseTaskException&)>& onException) {
    const auto remaining = std::make_shared<std::atomic<size_t>>(tasks_.size());
    for (const auto& task : tasks_) {
        task->run([remaining, onSuccess] -> void {
            if (remaining->fetch_sub(1, std::memory_order_release) == 1) {
                std::atomic_thread_fence(std::memory_order_acquire);
                onSuccess();
            }
        }, [remaining, onException](const BaseTaskException& e) -> void {
            if (remaining->fetch_sub(1, std::memory_order_release) == 1) {
                std::atomic_thread_fence(std::memory_order_acquire);
                onException(e);
            }
        });
    }
}

void TaskGroup::addTask(std::unique_ptr<BaseTask> task) {
    tasks_.push_back(std::move(task));
}
