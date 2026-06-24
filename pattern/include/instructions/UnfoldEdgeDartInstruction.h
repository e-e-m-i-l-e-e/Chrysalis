#ifndef CHRYSALIS_UNFOLDEDGEDARTINSTRUCTION_H
#define CHRYSALIS_UNFOLDEDGEDARTINSTRUCTION_H

#include "instructions/BasePatternInstruction.h"

namespace Chrysalis {
    class UnfoldEdgeDartInstruction: public BasePatternInstruction {
    public:
        explicit UnfoldEdgeDartInstruction(ProjectSpace* space, SelectedPatternsArgument* patterns,
                                           const name* edgePointFrom, const name* edgePointTo,
                                           const name* apexPoint, const name* leg1Point, const num* intake);
        ~UnfoldEdgeDartInstruction() override;

        bool isValid() override;
        void execute() override;
    private:
        const name* edgePointFrom_;
        const name* edgePointTo_;
        const name* apexPoint_;
        const name* leg1Point_;
        const num* intake_;
    };
}

#endif //CHRYSALIS_UNFOLDEDGEDARTINSTRUCTION_H