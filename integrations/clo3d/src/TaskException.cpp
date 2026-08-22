#include "TaskException.h"

using namespace CLO3D;

TaskException::TaskException(const QString& taskName, const char* message)
    : task_(taskName), message_(message) {}

const QString& TaskException::name() const {
    return task_;
}

const char* TaskException::what() const noexcept {
    return BaseTaskException::what();
}
