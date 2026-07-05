#ifndef CHRYSALIS_BASEPROJECTS_H
#define CHRYSALIS_BASEPROJECTS_H

#include "Project.h"

namespace Chrysalis {
    class BaseProjectComposer {
    protected:
        explicit BaseProjectComposer(Project* project);
        virtual ~BaseProjectComposer() = default;

    public:
        void fill();
        virtual void fillOptions() = 0;
        virtual void fillPatterns() = 0;
        virtual void fillParameters() = 0;
        virtual void fillInstructions() = 0;
    protected:
        Project* project_;
    };
}

#endif //CHRYSALIS_BASEPROJECTS_H