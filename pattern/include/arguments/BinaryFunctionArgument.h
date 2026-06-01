#ifndef CHRYSALIS_BINARYFUNCTIONARGUMENT_H
#define CHRYSALIS_BINARYFUNCTIONARGUMENT_H

#include <functional>

#include "NumberArgument.h"

namespace Chrysalis {
    struct BinaryFunction {
        static boost::optional<double> add(const NumberArgument* operand1, const NumberArgument* operand2);
        static boost::optional<double> subtract(const NumberArgument* operand1, const NumberArgument* operand2);
        static boost::optional<double> multiply(const NumberArgument* operand1, const NumberArgument* operand2);
        static boost::optional<double> divide(const NumberArgument* operand1, const NumberArgument* operand2);
    private:
        static boost::optional<double> evaluate(const NumberArgument* operand1, const NumberArgument* operand2,
                                                const std::function<double(double a, double n)>& evaluator);
    };

    class BinaryFunctionArgument: public NumberArgument {
    public:
        explicit BinaryFunctionArgument(const NumberArgument* operand1, const NumberArgument* operand2,
                                        const boost::optional<double> (BinaryFunction::*function)(const NumberArgument* operand1, const NumberArgument* operand2));
        ~BinaryFunctionArgument() override;
    private:
        /// @uml{composition}
        const NumberArgument* operand1_;
        /// @uml{composition}
        const NumberArgument* operand2_;
        const boost::optional<double> (BinaryFunction::*function_)(const NumberArgument* operand1, const NumberArgument* operand2);

        static inline BinaryFunction evaluator;
    };
}

#endif //CHRYSALIS_BINARYFUNCTIONARGUMENT_H