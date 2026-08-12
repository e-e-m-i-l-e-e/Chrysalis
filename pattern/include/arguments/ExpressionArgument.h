#ifndef CHRYSALIS_EXPRESSIONARGUMENT_H
#define CHRYSALIS_EXPRESSIONARGUMENT_H

#include "Expression.h"
#include "arguments/Argument.h"
#include "arguments/BaseCalculatedArgument.h"

namespace Chrysalis {
    class ExpressionArgument: public BaseCalculatedArgument<double> {
        PROVIDE_SERIALIZATION_ACCESS(ExpressionArgument)
    public:
        explicit ExpressionArgument(const ExpressionsContainer* expressions, const args::name* name);
        ~ExpressionArgument() override;
    protected:
        std::expected<double, Error> calculate() const override;
    private:
        const ExpressionsContainer* expressions_;
        /// @uml{composition}
        const args::name* name_;
    };
    namespace args {
        using expr = Expression;
    }
    SERIALIZE_DERIVED_CONSTRUCTION(ExpressionArgument, BaseCalculatedArgument<double>, expressions_, name_)
}

#endif //CHRYSALIS_EXPRESSIONARGUMENT_H