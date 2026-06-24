#ifndef CHRYSALIS_MOVEPOINTINSTRUCTION_H
#define CHRYSALIS_MOVEPOINTINSTRUCTION_H

#include "BasePatternInstruction.h"

namespace Chrysalis {
    class MovePointInstruction: public BasePatternInstruction {
    public:
        explicit MovePointInstruction(ProjectSpace* space, SelectedPatternsArgument* patterns, const name* pointName,
                                      const num* angle, const num* length);
        ~MovePointInstruction() override = default;

        bool isValid() override;
        void execute() override;
    private:
        const name* pointName_;
        const num* angle_;
        const num* length_;
    };
}

#endif //CHRYSALIS_MOVEPOINTINSTRUCTION_H