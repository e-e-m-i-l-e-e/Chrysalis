#ifndef CHRYSALIS_CURVEINSTRUCTION_H
#define CHRYSALIS_CURVEINSTRUCTION_H

#include "CompositiveContainer.h"
#include "arguments/VectorArgument.h"
#include "arguments/PatternPointArgument.h"
#include "instructions/BasePatternInstruction.h"

namespace Chrysalis {
    class CurveInstruction: public BasePatternInstruction {
        PROVIDE_SERIALIZATION_ACCESS(CurveInstruction)
    public:
        explicit CurveInstruction(ProjectSpace* space, args::patterns* patterns,
                                  const args::vector* from, const args::vector* to,
                                  const args::container<PatternPointArgument>* points);
        ~CurveInstruction() override;

        bool isValid() override;
        void execute() override;
    private:
        /// @uml{composition}
        const args::vector* from_;
        /// @uml{composition}
        const args::vector* to_;
        /// @uml{composition}
        const args::container<PatternPointArgument>* points_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(CurveInstruction, BasePatternInstruction, space_, patterns_, from_, to_, points_);
}

#endif //CHRYSALIS_CURVEINSTRUCTION_H