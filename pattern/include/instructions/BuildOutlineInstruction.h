#ifndef CHRYSALIS_STARTOUTLINEINSTRUCTION_H
#define CHRYSALIS_STARTOUTLINEINSTRUCTION_H

#include "BasePatternInstruction.h"

namespace Chrysalis {
    using name = NameArgument;
    /**
     * @uml{note[top] Syntax samples:
     * out -> A -> B -> C // (3 instructions)
     * out("Name") -> A -> B -> C
     * }
     */
    class BuildOutlineInstruction: public BasePatternInstruction {
    public:
        explicit BuildOutlineInstruction(ProjectSpace* space, SelectedPatternsArgument* selectedPatterns,
                                         name* outlineName, name* point);
        ~BuildOutlineInstruction() override;

        void execute() override;
        bool isValid() override;
    private:
        name* outlineName_;
        name* point_;
    };
}

#endif //CHRYSALIS_STARTOUTLINEINSTRUCTION_H