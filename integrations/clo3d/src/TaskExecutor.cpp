#include "TaskExecutor.h"

#include <QFuture>
#include <QFutureWatcher>

using namespace CLO3D;

void TaskExecutor::submit(std::unique_ptr<BaseTask> task, const std::function<void()>& onSuccess) {
    auto it = tasks_.insert(tasks_.end(), std::move(task));
    (*it)->run([this, it, onSuccess] -> void {
        onSuccess();
        tasks_.erase(it);
    });
}
