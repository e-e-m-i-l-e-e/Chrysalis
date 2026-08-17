#ifndef CHRYSALIS_TASKEXECUTOR_H
#define CHRYSALIS_TASKEXECUTOR_H

#include <list>
#include <memory>
#include <functional>
#include <unordered_map>

#include "BaseTask.h"
#include "CLO3DExtensionExport.h"

namespace CLO3D {
    class CLO3D_EXTENSION TaskExecutor {
    public:
        TaskExecutor() = default;

        // Non-copyable: tasks_ holds move-only unique_ptr<BaseTask> entries,
        // so an implicit copy would be deleted anyway - declared explicitly
        // to avoid MSVC's dllexport implicit-instantiation of the deleted
        // copy assignment operator (a known MSVC quirk for exported classes
        // with move-only members).
        TaskExecutor(const TaskExecutor&) = delete;
        TaskExecutor& operator=(const TaskExecutor&) = delete;

        void submit(std::unique_ptr<BaseTask> task, const std::function<void()>& onSuccess);
    private:
        std::list<std::unique_ptr<BaseTask>> tasks_{};
    };
}

#endif // CHRYSALIS_TASKEXECUTOR_H
