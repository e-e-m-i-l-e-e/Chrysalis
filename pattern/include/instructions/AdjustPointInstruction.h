#ifndef CHRYSALIS_ADJUSTPOINTINSTRUCTION_H
#define CHRYSALIS_ADJUSTPOINTINSTRUCTION_H

#include <boost/serialization/export.hpp>

#include "BasePatternInstruction.h"
#include "arguments/VectorArgument.h"
#include "arguments/PatternPointArgument.h"

namespace Chrysalis {
    class AdjustPointInstruction: public BasePatternInstruction {
        PROVIDE_SERIALIZATION_ACCESS(AdjustPointInstruction)
    public:
        /**
         * @uml{note[top] Syntax samples:
         * B -10-> A <-15- C
         */
        explicit AdjustPointInstruction(ProjectSpace* space, args::patterns* patterns, const args::point* target,
                                        const args::vector* vector1, const args::vector* vector2);
        ~AdjustPointInstruction() override;

        bool isValid() override;
        void execute() override;
    private:
        const args::point* target_;
        const args::vector* vector1_;
        const args::vector* vector2_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(AdjustPointInstruction, BasePatternInstruction, space_, patterns_, target_, vector1_, vector2_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::AdjustPointInstruction)

#endif //CHRYSALIS_ADJUSTPOINTINSTRUCTION_H