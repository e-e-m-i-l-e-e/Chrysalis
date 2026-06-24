#ifndef CHRYSALIS_INTERSECTIONPOINTINSTRUCTION_H
#define CHRYSALIS_INTERSECTIONPOINTINSTRUCTION_H

#include "BasePatternInstruction.h"

namespace Chrysalis {
    class IntersectionPointInstruction: public BasePatternInstruction {
    public:
        explicit IntersectionPointInstruction(ProjectSpace* space, SelectedPatternsArgument* patterns, const name* pointName,
                                              const name* pointFrom1, const name* pointTo1,
                                              const name* pointFrom2, const name* pointTo2);
        ~IntersectionPointInstruction() override;

        bool isValid() override;
        void execute() override;
    private:
        const name* pointName_;
        const name* pointFrom1_;
        const name* pointTo1_;
        const name* pointFrom2_;
        const name* pointTo2_;
    };
}

#endif //CHRYSALIS_INTERSECTIONPOINTINSTRUCTION_H