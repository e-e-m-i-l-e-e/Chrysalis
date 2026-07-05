#ifndef CHRYSALIS_EXPRESSION_H
#define CHRYSALIS_EXPRESSION_H

#include "BaseNamedElement.h"
#include "NamedElementsContainer.h"
#include "arguments/BaseCalculatedArgument.h"

namespace Chrysalis {
    class Expression: public BaseNamedElement, public BaseCalculatedArgument<double> {
        PROVIDE_DEFAULT_SERIALIZATION_ACCESS(Expression)
        SERIALIZE_DERIVED_FROM(BaseNamedElement, expression_)
    public:
        explicit Expression(const std::string& name, const args::number* expression);
        ~Expression() override;

        [[nodiscard]] bool isValid() const override;
    protected:
        double calculate() const override;
    private:
        const args::number* expression_;
    };
    namespace args {
        using expr = Expression;
    }
    using ExpressionsContainer = NamedElementsContainer<Expression>;
}

#endif //CHRYSALIS_EXPRESSION_H