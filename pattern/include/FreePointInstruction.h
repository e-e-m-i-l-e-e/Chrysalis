#ifndef CHRYSALIS_FREEPOINTINSTRUCTION_H
#define CHRYSALIS_FREEPOINTINSTRUCTION_H

#include "ProjectSpace.h"
#include "BasePatternInstruction.h"

namespace Chrysalis {
    /**
     * @uml{note[top] Syntax samples:
     * A (1, 1)
     * "A 1" (1.0, 2)
     * A (exp() exp())}
     */
    class FreePointInstruction: public BasePatternInstruction {
    public:
        explicit FreePointInstruction(ProjectSpace* space, SelectedPatternsArgument* patterns,
                                      const name* pointName, const num* x, const num* y);
        ~FreePointInstruction() override;

        bool isValid() override;
        void execute() const override;
    private:
        const name* pointName_;
        const num* x_;
        const num* y_;
    };
}

#endif //CHRYSALIS_FREEPOINTINSTRUCTION_H