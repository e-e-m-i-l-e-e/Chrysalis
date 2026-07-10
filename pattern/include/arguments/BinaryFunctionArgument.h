#ifndef CHRYSALIS_BINARYFUNCTIONARGUMENT_H
#define CHRYSALIS_BINARYFUNCTIONARGUMENT_H

#include "arguments/BaseCalculatedArgument.h"

#define BINARY_FUNCTIONS (Add)(Subtract)(Multiply)(Divide)(Min)(Max)

namespace Chrysalis {
    class BinaryFunctionArgument: public BaseCalculatedArgument<double> {
        SERIALIZE_DERIVED_FROM(BaseCalculatedArgument)
    protected:
        explicit BinaryFunctionArgument(const args::number* operand1, const args::number* operand2);
    public:
        ~BinaryFunctionArgument() override;

        #define FORWARD_DECLARE(r, data, Name) class Name;
        BOOST_PP_SEQ_FOR_EACH(FORWARD_DECLARE, _, BINARY_FUNCTIONS)
        #undef FORWARD_DECLARE

        bool isValid() const override;
    protected:
        double calculate() const override;
        virtual double evaluate(double a, double b) const = 0;

        /// @uml{composition}
        const args::number* operand1_;
        /// @uml{composition}
        const args::number* operand2_;
    };

    #define DECLARE_BINARY_FUNCTION(r, data, Name)                                                                     \
    class BinaryFunctionArgument::Name: public BinaryFunctionArgument {                                                \
        PROVIDE_SERIALIZATION_ACCESS(BinaryFunctionArgument::Name)                                                     \
    public:                                                                                                            \
        explicit Name(const args::number* operand1, const args::number* operand2)                                      \
                 : BinaryFunctionArgument(operand1, operand2) {}                                                       \
    protected:                                                                                                         \
        double evaluate(double a, double b) const override;                                                            \
    };                                                                                                                 \
    SERIALIZE_DERIVED_CONSTRUCTION(BinaryFunctionArgument::Name, BinaryFunctionArgument, operand1_, operand2_);
    BOOST_PP_SEQ_FOR_EACH(DECLARE_BINARY_FUNCTION, _, BINARY_FUNCTIONS)
    #undef DECLARE_BINARY_FUNCTION
}

#endif //CHRYSALIS_BINARYFUNCTIONARGUMENT_H