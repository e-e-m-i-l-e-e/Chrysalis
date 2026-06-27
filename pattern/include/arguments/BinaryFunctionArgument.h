#ifndef CHRYSALIS_BINARYFUNCTIONARGUMENT_H
#define CHRYSALIS_BINARYFUNCTIONARGUMENT_H

#include "BinaryFunction.h"
#include "BaseCalculatedArgument.h"

namespace Chrysalis {
    class SERIALIZABLE(BinaryFunctionArgument): public BaseCalculatedArgument<double> {
        PROVIDE_SERIALIZATION_ACCESS(BinaryFunctionArgument)
    public:
        explicit BinaryFunctionArgument(const num* operand1, const num* operand2, const BinaryFunction* function);
        ~BinaryFunctionArgument() override;

        bool isValid() const override;
    protected:
        double calculate() const override;
    private:
        /// @uml{composition}
        const num* operand1_;
        /// @uml{composition}
        const num* operand2_;
        /// @uml{composition}
        const BinaryFunction* function_;
    };
    SIMPLE_SERIALIZE_DERIVED_MEMBERS(BinaryFunctionArgument, BaseCalculatedArgument<double>, operand1_, operand2_, function_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::BinaryFunctionArgument)

#endif //CHRYSALIS_BINARYFUNCTIONARGUMENT_H