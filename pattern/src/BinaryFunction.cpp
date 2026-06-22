#include "arguments/BinaryFunction.h"

using namespace Chrysalis;

#define IMPLEMENT_BINARY_FUNCTION(Name, functor)                                                                       \
boost::optional<double> BinaryFunction::Name::evaluate(const num* operand1, const num* operand2) const {               \
    return BinaryFunction::evaluate(operand1, operand2, functor{});                                                    \
}

IMPLEMENT_BINARY_FUNCTION(Add, std::plus)
IMPLEMENT_BINARY_FUNCTION(Subtract, std::minus)
IMPLEMENT_BINARY_FUNCTION(Multiply, std::multiplies)
IMPLEMENT_BINARY_FUNCTION(Divide, std::divides)

boost::optional<double> BinaryFunction::evaluate(const num* operand1, const num* operand2,
                                                 const std::function<double(double a, double b)>& evaluator) {
    if (!operand1->hasArgument() && !operand2->hasArgument()) return boost::none;
    return evaluator(operand1->getArgument(), operand2->getArgument());
}