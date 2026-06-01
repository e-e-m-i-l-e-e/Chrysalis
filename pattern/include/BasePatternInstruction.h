#ifndef CHRYSALIS_BASEPATTERNINSTRUCTION_H
#define CHRYSALIS_BASEPATTERNINSTRUCTION_H

#include "ProjectSpace.h"
#include "PatternSpacesArgument.h"

namespace Chrysalis {
    class BasePatternInstruction {
    public:
        virtual ~BasePatternInstruction();
    protected:
        explicit BasePatternInstruction(ProjectSpace* space, Argument<PatternSpacesArgument*>* patternSpaces);

        virtual bool isValid() = 0;
        virtual void execute() = 0;

        [[nodiscard]] ProjectSpace& space() const {
            return *space_;
        }
        [[nodiscard]] PatternSpacesArgument& patterns() const {
            return *patternSpaces_->getArgument();
        }
    private:
        ProjectSpace* space_;
        Argument<PatternSpacesArgument*>* patternSpaces_;
    };
};

#endif //CHRYSALIS_BASEPATTERNINSTRUCTION_H