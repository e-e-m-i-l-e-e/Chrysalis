#ifndef CHRYSALIS_STARTOUTLINEINSTRUCTION_H
#define CHRYSALIS_STARTOUTLINEINSTRUCTION_H

#include <boost/serialization/export.hpp>

#include "arguments/Argument.h"
#include "arguments/OptionalArgument.h"
#include "arguments/PatternsContainerArgument.h"
#include "BasePatternInstruction.h"
#include "BuildOutlineInstruction.h"
#include "arguments/PatternPointArgument.h"

namespace Chrysalis {
    /**
     * @uml{note[top] Syntax samples:
     * out -> A -> B -> C // (3 instructions)
     * out("Name") -> A -> B -> C
     * }
     */
    class BuildOutlineInstruction: public BasePatternInstruction {
        PROVIDE_SERIALIZATION_ACCESS(BuildOutlineInstruction)
    public:
        explicit BuildOutlineInstruction(ProjectSpace* space, args::patterns* selectedPatterns,
                                         const args::name* outlineName, const PatternPointArgument* point);
        ~BuildOutlineInstruction() override;

        void execute() override;
    private:
        const args::name* outlineName_;
        const PatternPointArgument* point_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(BuildOutlineInstruction, BasePatternInstruction, space_, patterns_, outlineName_, point_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::BuildOutlineInstruction)

#endif //CHRYSALIS_STARTOUTLINEINSTRUCTION_H