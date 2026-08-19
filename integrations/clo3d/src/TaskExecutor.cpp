#include "TaskExecutor.h"

#include <QFuture>
#include <QFutureWatcher>

using namespace CLO3D;

void TaskExecutor::wait(const QString& task) {
    auto it = tasks_.find(task.toStdString());
    if (it == tasks_.end()) return;
    it->second->wait();
}

void TaskExecutor::submit(std::unique_ptr<BaseTask> task) {
    const auto it = tasks_.emplace(task->name().toStdString(), std::move(task)).first;
    it->second->run([]{}, [](const BaseTaskException&){});
    it->second->wait();
    tasks_.erase(it);
}

void TaskExecutor::submit(std::unique_ptr<BaseTask> task, const std::function<void()>& onSuccess, const std::function<void(const BaseTaskException&)>& onException) {
    auto it = tasks_.emplace(task->name().toStdString(), std::move(task)).first;
    it->second->run([this, it, onSuccess] -> void {
        onSuccess();
        tasks_.erase(it);
    }, [this, it, onException](const BaseTaskException& e) -> void {
        onException(e);
        tasks_.erase(it);
    });
}
