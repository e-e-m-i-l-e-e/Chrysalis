#include "Task.h"

#include <functional>

#include <QFutureWatcher>
#include <QtConcurrentRun>

#include "BaseTask.h"
#include "TaskException.h"
#include "BaseTaskException.h"

#include "Logging.h"
#define LOGGER_NAME "Task Executor: Task"

using namespace CLO3D;

Task::Task(const QString& name, const std::function<void()>& task): BaseTask(name), task_(task) {
    LOG_TRACE("\"{}\" task have been created.", name.toStdString());
}

void Task::wait() {
    future_.waitForFinished();
}

void Task::run(const std::function<void()>& onSuccess, const std::function<void(const BaseTaskException&)>& onException) {
    const auto watcher = new QFutureWatcher<void>();
    QObject::connect(watcher, &QFutureWatcher<void>::finished, [this, watcher, onSuccess, onException] -> void {
        try {
            future_.waitForFinished();
            onSuccess();
        } catch (const std::exception& e) {
            onException(TaskException(name(), e.what()));
        } catch (...) {
            LOG_ERROR("Unknown exception thrown in \"{}\" task.", name().toStdString());
        }
        watcher->deleteLater();
    });
    future_ = QtConcurrent::run(task_);
    watcher->setFuture(future_);
}