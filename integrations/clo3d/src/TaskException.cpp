#include "TaskException.h"

using namespace CLO3D;

TaskException::TaskException(const QString& taskName, const QString& message)
    : task_(taskName), message_(message){}

QString TaskException::name() const {
    return task_;
}

QString TaskException::message() const {
    return message_;
}
