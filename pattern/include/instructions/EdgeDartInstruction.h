#ifndef CHRYSALIS_DARTINSTRUCTION_H
#define CHRYSALIS_DARTINSTRUCTION_H

#include "BasePatternInstruction.h"

namespace Chrysalis {
    class EdgeDartInstruction: public BasePatternInstruction {
    public:
        explicit EdgeDartInstruction(ProjectSpace* space, SelectedPatternsArgument* patterns,
                                     const name* edgePointFrom, const name* edgePointTo, const name* dartPoint,
                                     const num* angle, const num* length, const num* leg1Intake, const num* leg2Intake);
        ~EdgeDartInstruction() override;

        bool isValid() override;
        void execute() override;
    private:
        const name* edgePointFrom_;
        const name* edgePointTo_;
        const name* dartPoint_;
        const num* angle_;
        const num* length_;
        const num* leg1Intake_;
        const num* leg2Intake_;
    };
}

#endif //CHRYSALIS_DARTINSTRUCTION_H