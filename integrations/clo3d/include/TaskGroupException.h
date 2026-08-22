#ifndef CHRYSALIS_TASKGROUPEXCEPTION_H
#define CHRYSALIS_TASKGROUPEXCEPTION_H

#include <string>
#include <vector>
#include <stdexcept>

#include <QString>

#include "BaseTaskException.h"

namespace CLO3D {
    class CLO3D_EXTENSION TaskGroupException: public BaseTaskException {
    public:
        explicit TaskGroupException(const QString& groupName);

        const QString& name() const override;
        [[nodiscard]] const char* what() const noexcept override;

        bool empty() const;
        void addException(const BaseTaskException& e);
    private:
        const QString groupName;
        std::vector<std::pair<QString, QString>> tasksMessages;
    };
}

#endif // CHRYSALIS_TASKGROUPEXCEPTION_H
