#ifndef CHRYSALIS_EXPRESSIONINSTRUCTION_H
#define CHRYSALIS_EXPRESSIONINSTRUCTION_H

#include "arguments/ExpressionArgument.h"
#include "instructions/BaseInstruction.h"

/** @defgroup Instructions Instructions
 *  @{
 */
namespace Chrysalis {
    class ExpressionInstruction: public BaseInstruction {
        PROVIDE_SERIALIZATION_ACCESS(ExpressionInstruction)
    public:
        explicit ExpressionInstruction(ExpressionsContainer* expressions, args::name&& name, args::number&& value);
        void execute() override;
    private:
        ExpressionsContainer* expressions_;
        /// @uml{composition}
        args::name name_;
        args::number value_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(ExpressionInstruction, BaseInstruction, expressions_, name_, value_)
}
/**@}*/

#endif //CHRYSALIS_EXPRESSIONINSTRUCTION_H