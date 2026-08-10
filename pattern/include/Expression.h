#ifndef CHRYSALIS_EXPRESSION_H
#define CHRYSALIS_EXPRESSION_H

#include "BaseNamedElement.h"
#include "ScopedNamedElementsContainer.h"
#include "arguments/BaseCalculatedArgument.h"

namespace Chrysalis {
    struct ExpressionValue {
        operator double() const;
        double value;
    };
    class Expression: public BaseNamedElement, public BaseCalculatedArgument<ExpressionValue> {
        PROVIDE_DEFAULT_SERIALIZATION_ACCESS(Expression)
        SERIALIZE_DERIVED_FROM(BaseNamedElement, expression_)
    public:
        explicit Expression(const std::string& name, const args::number* expression);
        ~Expression() override;

        [[nodiscard]] bool isValid() const override;
    protected:
        ExpressionValue calculate() const override;
    private:
        const args::number* expression_;
    };
    using ExpressionsContainer = ScopedNamedElementsContainer<Expression>;
}

#endif //CHRYSALIS_EXPRESSION_H