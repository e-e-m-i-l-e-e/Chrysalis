#include "TaskGroupException.h"

using namespace CLO3D;

TaskGroupException::TaskGroupException(const QString& groupName): groupName(groupName) {}

QString TaskGroupException::name() const {
    return groupName;
}

QString TaskGroupException::message() const {
    QString errorMessage = groupName + ":";
    for (const auto& [name, message]: tasksMessages) {
        errorMessage.append("\n\t").append(name).append(": ").append(message);
    }
    return errorMessage;
}

bool TaskGroupException::empty() const {
    return tasksMessages.empty();
}

void TaskGroupException::addException(const BaseTaskException& e) {
    tasksMessages.emplace_back(e.name(), e.message());
}
