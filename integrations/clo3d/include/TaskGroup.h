#ifndef CLO3D_TASKGROUP_H
#define CLO3D_TASKGROUP_H

#include <memory>
#include <functional>

#include "BaseTask.h"
#include "CLO3DExtensionExport.h"

namespace CLO3D {
    class CLO3D_EXTENSION TaskGroup: public BaseTask {
    public:
        explicit TaskGroup(const QString& name);

        void addTask(std::unique_ptr<BaseTask> task);
    protected:
        void run(const std::function<void()>& onSuccess) override;
    private:
        std::vector<std::unique_ptr<BaseTask>> tasks_;
    };
}

#endif // CLO3D_TASKGROUP_H
