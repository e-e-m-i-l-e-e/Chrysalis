#ifndef CHRYSALIS_FREEPOINTINSTRUCTION_H
#define CHRYSALIS_FREEPOINTINSTRUCTION_H

#include "PatternSpacesArgument.h"
#include "ProjectSpace.h"
#include "BasePatternInstruction.h"
#include "NameArgument.h"
#include "NumberArgument.h"

namespace Chrysalis {
    using name = NameArgument;
    using num = NumberArgument;
    /**
     * @uml{note[top] Syntax samples:
     * A (1, 1)
     * "A 1" (1.0, 2)
     * A (exp() exp())}
     */
    class FreePointInstruction: public BasePatternInstruction {
    public:
        explicit FreePointInstruction(ProjectSpace* space,
                                      Argument<PatternSpacesArgument*>* patternSpaces, name* pointName,
                                      num* x, num* y);
        ~FreePointInstruction() override;

        bool isValid() override;
        void execute() override;
    private:
        name* pointName_;
        num* x_;
        num* y_;
    };
}

#endif //CHRYSALIS_FREEPOINTINSTRUCTION_H