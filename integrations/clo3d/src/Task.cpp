#include "Task.h"

#include <QFutureWatcher>
#include <QtConcurrentRun>

using namespace CLO3D;

Task::Task(const QString& name, const std::function<void()>& task): BaseTask(name), task_(task) {}

void Task::run(const std::function<void()>& onSuccess) {
    const auto watcher = new QFutureWatcher<void>();
    QObject::connect(watcher, &QFutureWatcher<void>::finished, onSuccess);
    // QObject::connect(watcher, &QFutureWatcher<void>::finished, &QFutureWatcher<void>::deleteLater);
    watcher->setFuture(QtConcurrent::run(task_));
}