#ifndef CHRYSALIS_BINARYFUNCTIONARGUMENT_H
#define CHRYSALIS_BINARYFUNCTIONARGUMENT_H

#include "BinaryFunction.h"

namespace Chrysalis {
    class SERIALIZABLE(BinaryFunctionArgument): public NumberArgument {
        PROVIDE_SERIALIZATION_ACCESS(BinaryFunctionArgument)
    public:
        explicit BinaryFunctionArgument(const num* operand1, const num* operand2, const BinaryFunction* function);
        ~BinaryFunctionArgument() override;
    private:
        /// @uml{composition}
        const num* operand1_;
        /// @uml{composition}
        const num* operand2_;
        /// @uml{composition}
        const BinaryFunction* function_;
    };
    SIMPLE_SERIALIZE_DERIVED_MEMBERS(BinaryFunctionArgument, NumberArgument, operand1_, operand2_, function_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::BinaryFunctionArgument)

#endif //CHRYSALIS_BINARYFUNCTIONARGUMENT_H