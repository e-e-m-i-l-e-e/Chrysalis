#ifndef CHRYSALIS_STARTOUTLINEINSTRUCTION_H
#define CHRYSALIS_STARTOUTLINEINSTRUCTION_H

#include <boost/serialization/export.hpp>

#include "arguments/Argument.h"
#include "arguments/OptionalArgument.h"
#include "arguments/PatternsContainerArgument.h"
#include "BasePatternInstruction.h"
#include "BuildOutlineInstruction.h"
#include "arguments/PatternPointArgument.h"

/** @defgroup Instructions Instructions
 *  @{
 */
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
                                         args::name&& outlineName, const args::container<const PatternPointArgument>* points);
        ~BuildOutlineInstruction() override;

        void execute() override;
    private:
        args::name outlineName_;
        const args::container<const PatternPointArgument>* points_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(BuildOutlineInstruction, BasePatternInstruction, space_, patterns_, outlineName_, points_)
}
/**@}*/

#endif //CHRYSALIS_STARTOUTLINEINSTRUCTION_H