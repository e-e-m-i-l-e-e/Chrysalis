#ifndef CHRYSALIS_BINARYFUNCTIONARGUMENT_H
#define CHRYSALIS_BINARYFUNCTIONARGUMENT_H

#include "arguments/BaseCalculatedArgument.h"

#define BINARY_FUNCTIONS (Add)(Subtract)(Multiply)(Divide)(Min)(Max)

/** @defgroup Arguments Arguments
 *  @{
 */
namespace Chrysalis {
    class BinaryFunctionArgument: public BaseCalculatedArgument<double> {
        SERIALIZE_DERIVED_FROM(BaseCalculatedArgument)
    protected:
        explicit BinaryFunctionArgument(args::number&& operand1, args::number&& operand2);
    public:
        #define FORWARD_DECLARE(r, data, Name) class Name;
        BOOST_PP_SEQ_FOR_EACH(FORWARD_DECLARE, _, BINARY_FUNCTIONS)
        #undef FORWARD_DECLARE
    protected:
        std::expected<double, Error> calculate() const override;
        virtual std::expected<double, Error> evaluate(double a, double b) const = 0;

        /// @uml{composition}
        args::number operand1_;
        /// @uml{composition}
        args::number operand2_;
    };

    #define DECLARE_BINARY_FUNCTION(r, data, Name)                                                                     \
    class BinaryFunctionArgument::Name: public BinaryFunctionArgument {                                                \
        PROVIDE_SERIALIZATION_ACCESS(BinaryFunctionArgument::Name)                                                     \
    public:                                                                                                            \
        explicit Name(args::number&& operand1, args::number&& operand2)                                                \
                 : BinaryFunctionArgument(std::move(operand1), std::move(operand2)) {}                                 \
    protected:                                                                                                         \
        std::expected<double, Error> evaluate(double a, double b) const override;                                      \
    };                                                                                                                 \
    SERIALIZE_DERIVED_CONSTRUCTION(BinaryFunctionArgument::Name, BinaryFunctionArgument, operand1_, operand2_);
    BOOST_PP_SEQ_FOR_EACH(DECLARE_BINARY_FUNCTION, _, BINARY_FUNCTIONS)
    #undef DECLARE_BINARY_FUNCTION
}
/**@}*/

#endif //CHRYSALIS_BINARYFUNCTIONARGUMENT_H