#ifndef CHRYSALIS_BINARYFUNCTION_H
#define CHRYSALIS_BINARYFUNCTION_H

#include <boost/serialization/export.hpp>

#include "NumberArgument.h"

#define BINARY_FUNCTIONS (Add)(Subtract)(Multiply)(Divide)

#define FORWARD_DECLARE_BINARY_FUNCTION(r, data, Name)                                                                 \
class Name;

#define DECLARE_BINARY_FUNCTION(r, data, Name)                                                                         \
namespace Chrysalis {                                                                                                  \
    class BinaryFunction::Name: public BinaryFunction {                                                                \
    public:                                                                                                            \
        boost::optional<double> evaluate(const num* operand1, const num* operand2) const override;                     \
    };                                                                                                                 \
    SERIALIZE_DERIVED_MEMBERS(BinaryFunction::Name, BinaryFunction)                                                    \
}                                                                                                                      \
BOOST_CLASS_EXPORT_KEY(Chrysalis::BinaryFunction::Name)

namespace Chrysalis {
    using num = NumberArgument;
    class EMPTY_SERIALIZABLE(BinaryFunction) {
    protected:
        explicit BinaryFunction() = default;
    public:
        virtual ~BinaryFunction() = default;

        BOOST_PP_SEQ_FOR_EACH(FORWARD_DECLARE_BINARY_FUNCTION, _, BINARY_FUNCTIONS)

        virtual boost::optional<double> evaluate(const num* operand1, const num* operand2) const = 0;
    protected:
        static boost::optional<double> evaluate(const num* operand1, const num* operand2,
                                                const std::function<double(double a, double b)>& evaluator);
    };
}

BOOST_PP_SEQ_FOR_EACH(DECLARE_BINARY_FUNCTION, _, BINARY_FUNCTIONS)

#endif //CHRYSALIS_BINARYFUNCTION_H