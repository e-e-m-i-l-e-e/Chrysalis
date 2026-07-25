#ifndef CHRYSALIS_EXPRESSIONINSTRUCTION_H
#define CHRYSALIS_EXPRESSIONINSTRUCTION_H

#include "Expression.h"
#include "instructions/BaseInstruction.h"

namespace Chrysalis {
    class ExpressionInstruction: public BaseInstruction {
        PROVIDE_SERIALIZATION_ACCESS(ExpressionInstruction)
    public:
        explicit ExpressionInstruction(ExpressionsContainer* expressions, args::expr* expression);

        bool isValid() override;
        void execute() override;
    private:
        ExpressionsContainer* expressions_;
        // TODO: ownership ?
        args::expr* expression_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(ExpressionInstruction, BaseInstruction, expressions_, expression_)
}

#endif //CHRYSALIS_EXPRESSIONINSTRUCTION_H