#include "TaskExecutor.h"

#include <shared_mutex>

#include <QFuture>
#include <QFutureWatcher>

using namespace CLO3D;

void TaskExecutor::wait(const QString& taskName) {
    BaseTask* task = nullptr;
    {
        std::shared_lock lock(mutex_);
        const auto it = tasks_.find(taskName.toStdString());
        if (it == tasks_.end()) return;
        task = it->second.get();
    }
    task->wait();
}

void TaskExecutor::submit(std::unique_ptr<BaseTask> task) {
    BaseTask* t = task.get();
    submit(std::move(task), [] -> void {}, [](const BaseTaskException&) -> void {});
    t->wait();
}

void TaskExecutor::submit(std::unique_ptr<BaseTask> task, const std::function<void()>& onSuccess, const std::function<void(const BaseTaskException&)>& onException) {
    BaseTask* t = task.get();
    {
        // TODO: handle duplicates in names
        std::unique_lock lock(mutex_);
        const auto name = task->name().toStdString();
        tasks_.emplace(name, std::move(task));
    }
    t->run(onSuccess, onException);
}
