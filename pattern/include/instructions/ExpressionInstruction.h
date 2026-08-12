#ifndef CHRYSALIS_EXPRESSIONINSTRUCTION_H
#define CHRYSALIS_EXPRESSIONINSTRUCTION_H

#include "arguments/ExpressionArgument.h"
#include "instructions/BaseInstruction.h"

namespace Chrysalis {
    class ExpressionInstruction: public BaseInstruction {
        PROVIDE_SERIALIZATION_ACCESS(ExpressionInstruction)
    public:
        explicit ExpressionInstruction(ExpressionsContainer* expressions, const args::name* name, args::number&& value);
        ~ExpressionInstruction() override;

        void execute() override;
    private:
        ExpressionsContainer* expressions_;
        /// @uml{composition}
        const args::name* name_;
        args::number value_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(ExpressionInstruction, BaseInstruction, expressions_, name_, value_)
}

#endif //CHRYSALIS_EXPRESSIONINSTRUCTION_H