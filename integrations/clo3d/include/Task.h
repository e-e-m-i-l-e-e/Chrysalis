#ifndef CLO3D_TASK_H
#define CLO3D_TASK_H

#include <functional>

#include <QString>
#include <QFuture>

#include "BaseTask.h"
#include "CLO3DExtensionExport.h"

namespace CLO3D {
    class CLO3D_EXTENSION Task: public BaseTask {
    public:
        explicit Task(const QString& name, const std::function<void()>& task);
    protected:
        void wait() override;
        void run(const std::function<void()>& onSuccess, const std::function<void(const BaseTaskException&)>& onException) override;
    private:
        QFuture<void> future_;
        std::function<void()> task_;
    };
}

#endif // CLO3D_TASK_H
