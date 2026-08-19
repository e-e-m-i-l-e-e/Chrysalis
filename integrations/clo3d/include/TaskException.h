#ifndef CHRYSALIS_TASKEXCEPTION_H
#define CHRYSALIS_TASKEXCEPTION_H

#include <string>
#include <stdexcept>

#include <QString>

#include "BaseTaskException.h"

namespace CLO3D {
    class CLO3D_EXTENSION TaskException: public BaseTaskException {
    public:
        explicit TaskException(const QString& task, const QString& message);

        QString name() const override;
        QString message() const override;
    private:
        const QString task_;
        const QString message_;
    };
}

#endif // CHRYSALIS_TASKEXCEPTION_H
