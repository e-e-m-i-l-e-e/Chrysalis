#ifndef CHRYSALIS_BINARYFUNCTIONARGUMENT_H
#define CHRYSALIS_BINARYFUNCTIONARGUMENT_H

#include "arguments/BinaryFunction.h"
#include "arguments/BaseCalculatedArgument.h"

namespace Chrysalis {
    class BinaryFunctionArgument: public BaseCalculatedArgument {
        PROVIDE_SERIALIZATION_ACCESS(BinaryFunctionArgument)
    public:
        explicit BinaryFunctionArgument(const args::number* operand1, const args::number* operand2, const BinaryFunction* function);
        ~BinaryFunctionArgument() override;

        bool isValid() const override;
    protected:
        double calculate() const override;
    private:
        /// @uml{composition}
        const args::number* operand1_;
        /// @uml{composition}
        const args::number* operand2_;
        /// @uml{composition}
        const BinaryFunction* function_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(BinaryFunctionArgument, BaseCalculatedArgument, operand1_, operand2_, function_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::BinaryFunctionArgument)

#endif //CHRYSALIS_BINARYFUNCTIONARGUMENT_H