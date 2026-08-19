#ifndef CHRYSALIS_RESETTRANSFORMATIONINSTRUCTION_H
#define CHRYSALIS_RESETTRANSFORMATIONINSTRUCTION_H

#include "BasePatternInstruction.h"

/** @defgroup Instructions Instructions
 *  @{
 */
namespace Chrysalis {
    class ResetTransformationInstruction: public BasePatternInstruction {
        PROVIDE_SERIALIZATION_ACCESS(ResetTransformationInstruction)
    public:
        explicit ResetTransformationInstruction(ProjectSpace* space, args::patterns* patterns);

        void execute() override;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(ResetTransformationInstruction, BasePatternInstruction, space_, patterns_);
}
/**@}*/

#endif //CHRYSALIS_RESETTRANSFORMATIONINSTRUCTION_H
