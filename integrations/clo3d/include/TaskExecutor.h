#ifndef CHRYSALIS_TASKEXECUTOR_H
#define CHRYSALIS_TASKEXECUTOR_H

#include <memory>
#include <functional>
#include <unordered_map>

#include "BaseTask.h"
#include "CLO3DExtensionExport.h"

namespace CLO3D {
    class CLO3D_EXTENSION TaskExecutor {
    public:
        TaskExecutor() = default;
        TaskExecutor(const TaskExecutor&) = delete;
        TaskExecutor& operator=(const TaskExecutor&) = delete;

        void wait(const QString& task);
        void submit(std::unique_ptr<BaseTask> task);
        void submit(
            std::unique_ptr<BaseTask> task,
            const std::function<void()>& onSuccess,
            const std::function<void(const BaseTaskException&)>& onException = [](const BaseTaskException&) -> void {}
        );
    private:
        std::unordered_map<std::string, std::unique_ptr<BaseTask>> tasks_{};
    };
}

#endif // CHRYSALIS_TASKEXECUTOR_H
