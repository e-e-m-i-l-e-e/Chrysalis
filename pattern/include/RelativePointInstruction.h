#ifndef CHRYSALIS_ADDPOINTINSTRUCTION_H
#define CHRYSALIS_ADDPOINTINSTRUCTION_H

#include "BasePatternInstruction.h"

namespace Chrysalis {
    /**
     * \uml{note[top] Syntax samples:
     *
     * }
     */
    class RelativePointInstruction: public BasePatternInstruction {
    public:
        explicit RelativePointInstruction(ProjectSpace* space, SelectedPatternsArgument* selectedPatterns,
                                          const name* pointFrom, const pattern* pointFromPattern,
                                          const name* pointTo, const num* angle, const num* distance);
        ~RelativePointInstruction() override;

        bool isValid() override;
        void execute() const override;
    private:
        const name* pointFrom_;
        const pattern* pointFromPattern_;
        const name* pointTo_;
        const num* angle_;
        const num* distance_;
    };
}

#endif //CHRYSALIS_ADDPOINTINSTRUCTION_H