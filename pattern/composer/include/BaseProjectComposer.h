#ifndef CHRYSALIS_BASEPROJECTS_H
#define CHRYSALIS_BASEPROJECTS_H

#include "Project.h"

namespace Chrysalis {
    class BaseProjectComposer {
    protected:
        explicit BaseProjectComposer() = default;
        virtual ~BaseProjectComposer() = default;

    public:
        virtual Project* create() const = 0;

        void fill(Project* project);
        virtual void fillPatterns(Project* project) = 0;
        virtual void fillParameters(Project* project) = 0;
        virtual void fillInstructions(Project* project) = 0;
    };
}

#endif //CHRYSALIS_BASEPROJECTS_H