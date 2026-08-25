#include "TaskGroupException.h"


using namespace CLO3D;

TaskGroupException::TaskGroupException(const QString& groupName): groupName(groupName) {}

const QString& TaskGroupException::name() const {
    return groupName;
}

const char* TaskGroupException::what() const noexcept {
    QString errorMessage = groupName + ":";
    for (const auto& [name, message]: tasksMessages) {
        errorMessage.append("\n\t").append(name).append(": ").append(message);
    }
    const auto bytes = errorMessage.toUtf8();
    return bytes.constData();
}

bool TaskGroupException::empty() const {
    return tasksMessages.empty();
}

void TaskGroupException::addException(const BaseTaskException& e) {
    tasksMessages.emplace_back(e.name(), QString::fromUtf8(e.what()));
}
