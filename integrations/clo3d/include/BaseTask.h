#ifndef CLO3D_BASETASK_H
#define CLO3D_BASETASK_H

#include "BaseTaskException.h"


#include <functional>

#include <QString>

#include "CLO3DExtensionExport.h"

template <typename T>
class QFuture;
template <typename T>
class QFutureWatcher;

namespace CLO3D {
    class CLO3D_EXTENSION BaseTask {
        friend class TaskGroup;
        friend class TaskExecutor;
    public:
        explicit BaseTask(const QString& name);
        explicit BaseTask(const BaseTask&) = delete;
        explicit BaseTask(BaseTask&&) noexcept = delete;

        virtual ~BaseTask() = default;

        BaseTask& operator=(const BaseTask&) = delete;
        BaseTask& operator=(BaseTask&&) noexcept = delete;

        [[nodiscard]] const QString& name() const;
    protected:
        virtual void wait() = 0;
        virtual void run(const std::function<void()>& onSuccess, const std::function<void(const BaseTaskException&)>& onException) = 0;
    private:
        QString name_;
    };
}

#endif // CLO3D_BASETASK_H
