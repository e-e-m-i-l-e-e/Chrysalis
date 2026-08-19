#ifndef CHRYSALIS_FREEPOINTINSTRUCTION_H
#define CHRYSALIS_FREEPOINTINSTRUCTION_H

#include "arguments/Argument.h"
#include "instructions/BasePatternInstruction.h"

/** @defgroup Instructions Instructions
 *  @{
 */
namespace Chrysalis {
    /**
     * @uml{note[top] Syntax samples:
     * A (1, 1)
     * "A 1" (1.0, 2)
     * A (1 * 2 + 3, param("Circumference of something"))}
     */
    class FreePointInstruction: public BasePatternInstruction {
        PROVIDE_SERIALIZATION_ACCESS(FreePointInstruction)
    public:
        explicit FreePointInstruction(ProjectSpace* space, args::patterns* patterns,
                                      args::name&& pointName, args::number&& x, args::number&& y);
        void execute() override;
    private:
        args::name pointName_;
        args::number x_;
        args::number y_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(FreePointInstruction, BasePatternInstruction, space_, patterns_, pointName_, x_, y_)
}
/**@}*/

#endif //CHRYSALIS_FREEPOINTINSTRUCTION_H