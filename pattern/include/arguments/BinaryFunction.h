#ifndef CHRYSALIS_BINARYFUNCTION_H
#define CHRYSALIS_BINARYFUNCTION_H

#include <boost/serialization/export.hpp>

#include "arguments/BaseArgument.h"

#define BINARY_FUNCTIONS (Add)(Subtract)(Multiply)(Divide)

namespace Chrysalis {
    class BinaryFunction {
        SERIALIZED
    protected:
        explicit BinaryFunction() = default;
    public:
        virtual ~BinaryFunction() = default;

#define FORWARD_DECLARE(r, data, Name) class Name;
        BOOST_PP_SEQ_FOR_EACH(FORWARD_DECLARE, _, BINARY_FUNCTIONS)
#undef FORWARD_DECLARE

        virtual double evaluate(const args::number* operand1, const args::number* operand2) const = 0;
    protected:
        static double evaluate(const args::number* operand1, const args::number* operand2,
                               const std::function<double(double a, double b)>& evaluator);
    };
}

#define DECLARE_BINARY_FUNCTION(r, data, Name)                                                                         \
namespace Chrysalis {                                                                                                  \
    class BinaryFunction::Name: public BinaryFunction {                                                                \
        SERIALIZE_DERIVED_FROM(BinaryFunction)                                                                         \
    public:                                                                                                            \
        double evaluate(const args::number* operand1, const args::number* operand2) const override;                    \
    };                                                                                                                 \
}                                                                                                                      \
BOOST_CLASS_EXPORT_KEY(Chrysalis::BinaryFunction::Name)
BOOST_PP_SEQ_FOR_EACH(DECLARE_BINARY_FUNCTION, _, BINARY_FUNCTIONS)
#undef DECLARE_BINARY_FUNCTION

#undef BINARY_FUNCTIONS

#endif //CHRYSALIS_BINARYFUNCTION_H