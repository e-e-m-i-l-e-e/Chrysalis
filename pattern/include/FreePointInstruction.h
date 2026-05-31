#ifndef CHRYSALIS_FREEPOINTINSTRUCTION_H
#define CHRYSALIS_FREEPOINTINSTRUCTION_H

#include "PatternSpacesArgument.h"
#include "ProjectSpace.h"
#include "BaseInstruction.h"
#include "BasePatternSpacesInstruction.h"

namespace Chrysalis {
    /**
     * @uml{note[top] Syntax samples:
     * A (1, 1)
     * "A 1" (1.0, 2)
     * A (exp() exp())}
     */
    class FreePointInstruction: public BasePatternSpacesInstruction {
    public:
        explicit FreePointInstruction(ProjectSpace* space,
                                      Argument<PatternSpacesArgument*>* patternSpaces, Argument<std::string>* pointName,
                                      Argument<double>* x, Argument<double>* y);
        ~FreePointInstruction() override;

        void reset() override;
        bool isValid() override;
        void execute() override;
    private:
        Argument<std::string>* pointName_;
        Argument<double>* x_;
        Argument<double>* y_;
    };
}

#endif //CHRYSALIS_FREEPOINTINSTRUCTION_H