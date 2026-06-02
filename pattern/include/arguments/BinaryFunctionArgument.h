#ifndef CHRYSALIS_BINARYFUNCTIONARGUMENT_H
#define CHRYSALIS_BINARYFUNCTIONARGUMENT_H

#include <functional>

#include "NumberArgument.h"

namespace Chrysalis {
    using num = NumberArgument;
    struct BinaryFunction {
        boost::optional<double> add(const num* operand1, const num* operand2);
        boost::optional<double> subtract(const num* operand1, const num* operand2);
        boost::optional<double> multiply(const num* operand1, const num* operand2);
        boost::optional<double> divide(const num* operand1, const num* operand2);
    private:
        static boost::optional<double> evaluate(const num* operand1, const num* operand2,
                                                const std::function<double(double a, double n)>& evaluator);
    };

    class BinaryFunctionArgument: public NumberArgument {
    public:
        explicit BinaryFunctionArgument(const num* operand1, const num* operand2,
                                        boost::optional<double> (BinaryFunction::*function)(const num* operand1, const num* operand2));
        ~BinaryFunctionArgument() override;
    private:
        /// @uml{composition}
        const num* operand1_;
        /// @uml{composition}
        const num* operand2_;
        boost::optional<double> (BinaryFunction::*function_)(const num* operand1, const num* operand2);

        static inline BinaryFunction evaluator;
    };
}

#endif //CHRYSALIS_BINARYFUNCTIONARGUMENT_H