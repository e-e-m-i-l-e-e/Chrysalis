#ifndef CHRYSALIS_DARTINSTRUCTION_H
#define CHRYSALIS_DARTINSTRUCTION_H

#include "arguments/VectorArgument.h"
#include "arguments/PatternPointArgument.h"
#include "instructions/BasePatternInstruction.h"

namespace Chrysalis {
    class DartInstruction: public BasePatternInstruction {
        PROVIDE_SERIALIZATION_ACCESS(DartInstruction)
    public:
        explicit DartInstruction(ProjectSpace* space, args::patterns* patterns,
                                 const PatternPointArgument* point, const args::number* intake,
                                 const args::vector* top, const args::vector* bottom);
        ~DartInstruction() override;

        bool isValid() override;
        void execute() override;
    private:
        /// @uml{composition}
        const PatternPointArgument* point_;
        /// @uml{composition}
        const args::number* intake_;
        /// @uml{composition}
        const args::vector* top_;
        /// @uml{composition}
        const args::vector* bottom_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(DartInstruction, BasePatternInstruction, space_, patterns_, point_, intake_, top_, bottom_);
}

#endif //CHRYSALIS_DARTINSTRUCTION_H