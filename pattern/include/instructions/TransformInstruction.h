#ifndef CHRYSALIS_CONNECTINSTRUCTION_H
#define CHRYSALIS_CONNECTINSTRUCTION_H

#include "BasePatternInstruction.h"
#include "arguments/VectorArgument.h"

namespace Chrysalis {
    /**
     * @defgroup Instructions
     * @{
     */
    class TransformInstruction: public BasePatternInstruction {
        PROVIDE_SERIALIZATION_ACCESS(TransformInstruction)
    public:
        explicit TransformInstruction(ProjectSpace* space, args::patterns* patterns,
                                      const args::vector* from, const args::vector* to);
        ~TransformInstruction() override;

        void execute() override;
    private:
        /// @uml{composition}
        const args::vector* from_;
        /// @uml{composition}
        const args::vector* to_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(TransformInstruction, BasePatternInstruction, space_, patterns_, from_, to_);
}

#endif //CHRYSALIS_CONNECTINSTRUCTION_H
