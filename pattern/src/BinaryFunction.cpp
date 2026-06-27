#include "arguments/BinaryFunction.h"

using namespace Chrysalis;

#define IMPLEMENT_BINARY_FUNCTION(Name, functor)                                                                       \
double BinaryFunction::Name::evaluate(const num* operand1, const num* operand2) const {                                \
    return BinaryFunction::evaluate(operand1, operand2, functor{});                                                    \
}

IMPLEMENT_BINARY_FUNCTION(Add, std::plus)
IMPLEMENT_BINARY_FUNCTION(Subtract, std::minus)
IMPLEMENT_BINARY_FUNCTION(Multiply, std::multiplies)
IMPLEMENT_BINARY_FUNCTION(Divide, std::divides)

double BinaryFunction::evaluate(const num* operand1, const num* operand2,
                                const std::function<double(double a, double b)>& evaluator) {
    return evaluator(operand1->get(), operand2->get());
}