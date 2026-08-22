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

Task::~Task() {
    future_.waitForFinished();
}

void Task::wait() {
    future_.waitForFinished();
    if (exception_) throw *exception_;
}

void Task::run(const std::function<void()>& onSuccess, const std::function<void(const BaseTaskException&)>& onException) {
    future_ = QtConcurrent::run([this, onSuccess, onException] -> void {
        try {
            task_();
            onSuccess();
        } catch (const std::exception& e) {
            exception_.emplace(name(), e.what());
            onException(*exception_);
        } catch (...) {
            LOG_ERROR("Unknown exception thrown in \"{}\" task.", name().toStdString());
        }
    });
}