#ifndef CHRYSALIS_ADJUSTPOINTINSTRUCTION_H
#define CHRYSALIS_ADJUSTPOINTINSTRUCTION_H

#include <boost/serialization/export.hpp>

#include "BasePatternInstruction.h"
#include "arguments/VectorArgument.h"
#include "arguments/OptionalArgument.h"
#include "arguments/PatternPointArgument.h"

namespace Chrysalis {
    /**
     * @uml{note[top] Syntax samples:
     * B -10-> A <-15- C}
     */
    class MovePointInstruction: public BasePatternInstruction {
        PROVIDE_SERIALIZATION_ACCESS(MovePointInstruction)
    public:
        explicit MovePointInstruction(ProjectSpace* space, args::patterns* patterns, const PatternPointArgument* point,
                                        const args::vector* vector1, const args::optional<args::vector>* vector2);
        ~MovePointInstruction() override;

        void execute() override;
    private:
        const PatternPointArgument* point_;
        const args::vector* vector1_;
        const args::optional<args::vector>* vector2_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(MovePointInstruction, BasePatternInstruction, space_, patterns_, point_, vector1_, vector2_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::MovePointInstruction)

#endif //CHRYSALIS_ADJUSTPOINTINSTRUCTION_H