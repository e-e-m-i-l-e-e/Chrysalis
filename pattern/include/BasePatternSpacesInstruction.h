#ifndef CHRYSALIS_BASEPATTERNSPACESINSTRUCTION_H
#define CHRYSALIS_BASEPATTERNSPACESINSTRUCTION_H

#include "ProjectSpace.h"
#include "BaseInstruction.h"
#include "PatternSpacesArgument.h"

namespace Chrysalis {
    class BasePatternSpacesInstruction: public BaseInstruction {
    protected:
        explicit BasePatternSpacesInstruction(ProjectSpace* space, Argument<PatternSpacesArgument*>* patternSpaces);
        ~BasePatternSpacesInstruction() override;

        ProjectSpace* space_;
        Argument<PatternSpacesArgument*>* patternSpaces_;
    };
};

#endif //CHRYSALIS_BASEPATTERNSPACESINSTRUCTION_H