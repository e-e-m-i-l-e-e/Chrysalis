#ifndef CHRYSALIS_DARTINSTRUCTION_H
#define CHRYSALIS_DARTINSTRUCTION_H

#include "BasePatternInstruction.h"
#include "arguments/SelectedNamesArgument.h"

namespace Chrysalis {
    class DartInstruction: public BasePatternInstruction {
    public:
        explicit DartInstruction(ProjectSpace* space, SelectedPatternsArgument* patterns,
                                 const name* point, const num* angle, const num* length, const num* edgeAngle,
                                 const num* leg1Length, const num* leg2Length, const SelectedNamesArgument* selectedPoints);
        ~DartInstruction() override;

        bool isValid() override;
        void execute() override;
    private:
        const num* angle_;
        const num* length_;
        const name* point_;
        const num* edgeAngle_;
        const num* leg1Length_;
        const num* leg2Length_;
        const SelectedNamesArgument* selectedPoints_;
    };
}

#endif //CHRYSALIS_DARTINSTRUCTION_H