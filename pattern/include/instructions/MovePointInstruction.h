#ifndef CHRYSALIS_MOVEPOINTINSTRUCTION_H
#define CHRYSALIS_MOVEPOINTINSTRUCTION_H

#include <boost/serialization/export.hpp>

#include "arguments/VectorArgument.h"
#include "instructions/BasePatternInstruction.h"

namespace Chrysalis {
    class MovePointInstruction: public BasePatternInstruction {
        PROVIDE_SERIALIZATION_ACCESS(MovePointInstruction)
    public:
        explicit MovePointInstruction(ProjectSpace* space, args::patterns* patterns, const args::vector* vector);
        ~MovePointInstruction() override = default;

        bool isValid() override;
        void execute() override;
    private:
        const args::vector* vector_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(MovePointInstruction, BasePatternInstruction, space_, patterns_, vector_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::MovePointInstruction)

#endif //CHRYSALIS_MOVEPOINTINSTRUCTION_H