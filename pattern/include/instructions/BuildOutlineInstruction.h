#ifndef CHRYSALIS_STARTOUTLINEINSTRUCTION_H
#define CHRYSALIS_STARTOUTLINEINSTRUCTION_H

#include <boost/serialization/export.hpp>

#include "arguments/Argument.h"
#include "arguments/OptionalArgument.h"
#include "arguments/PatternsContainerArgument.h"
#include "BasePatternInstruction.h"
#include "BuildOutlineInstruction.h"

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
                                         args::name* outlineName, args::name* point);
        ~BuildOutlineInstruction() override;

        void execute() override;
        bool isValid() override;
    private:
        args::name* outlineName_;
        args::name* point_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(BuildOutlineInstruction, BasePatternInstruction, space_, patterns_, outlineName_, point_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::BuildOutlineInstruction)

#endif //CHRYSALIS_STARTOUTLINEINSTRUCTION_H