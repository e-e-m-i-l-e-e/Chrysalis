#include "BaseTask.h"

using namespace CLO3D;

BaseTask::BaseTask(const QString& name): name_(name) {}

const QString& BaseTask::name() const {
    return name_;
}