#ifndef CHRYSALIS_ADDPOINTINSTRUCTION_H
#define CHRYSALIS_ADDPOINTINSTRUCTION_H

#include <boost/serialization/export.hpp>

#include "arguments/VectorArgument.h"
#include "arguments/OptionalArgument.h"
#include "arguments/PatternPointArgument.h"
#include "arguments/PatternsContainerArgument.h"
#include "instructions/BasePatternInstruction.h"

namespace Chrysalis {
    /**
     * @uml{note[top] Syntax samples:
     * A -> B 45 10
     * "A 1" ("Back") -> "B 2" 1 / 2 * 3 param("Short alias")
     * A -> B (1 * 2 * 3 * 4) (1 / 2 / param("Circumference of something"))
     * }
     */
    class RelativePointInstruction: public BasePatternInstruction {
        PROVIDE_SERIALIZATION_ACCESS(RelativePointInstruction)
    public:
        explicit RelativePointInstruction(ProjectSpace* space, args::patterns* selectedPatterns,
                                          const args::name* name, const args::vector* vector);
        explicit RelativePointInstruction(ProjectSpace* space, args::patterns* selectedPatterns,
                                          const args::name* name, const args::vector* vector,
                                          const args::optional<args::line>* line);
        ~RelativePointInstruction() override;

        void execute() override;
    private:
        const args::name* name_;
        const args::vector* vector_;
        const args::optional<args::line>* line_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(RelativePointInstruction, BasePatternInstruction, space_, patterns_, name_, vector_, line_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::RelativePointInstruction)

#endif //CHRYSALIS_ADDPOINTINSTRUCTION_H