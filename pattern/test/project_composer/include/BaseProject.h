#ifndef CHRYSALIS_BASEPROJECTS_H
#define CHRYSALIS_BASEPROJECTS_H

#include "Project.h"

namespace Chrysalis {
    class BaseProject {
    protected:
        explicit BaseProject() = default;
        virtual ~BaseProject() = default;

    public:
        void fill(Project* project);
        virtual void fillPatterns(Project* project) = 0;
        virtual void fillParameters(Project* project) = 0;
        virtual void fillInstructions(Project* project) = 0;
    };
}

#endif //CHRYSALIS_BASEPROJECTS_H