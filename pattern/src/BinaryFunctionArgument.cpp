#include "arguments/BinaryFunctionArgument.h"

boost::optional<double> Chrysalis::BinaryFunction::add(const num* operand1, const num* operand2) {
    return evaluate(operand1, operand2, [](const double a, const double b) {
        return a + b;
    });
}

boost::optional<double> Chrysalis::BinaryFunction::subtract(const num* operand1, const num* operand2) {
    return evaluate(operand1, operand2, [](const double a, const double b) {
        return a - b;
    });
}

boost::optional<double> Chrysalis::BinaryFunction::multiply(const num* operand1, const num* operand2) {
    return evaluate(operand1, operand2, [](const double a, const double b) {
        return a * b;
    });
}

boost::optional<double> Chrysalis::BinaryFunction::divide(const num* operand1, const num* operand2) {
    return evaluate(operand1, operand2, [](const double a, const double b) {
        return a / b;
    });
}

boost::optional<double> Chrysalis::BinaryFunction::evaluate(const num* operand1, const num* operand2,
                                                            const std::function<double(double a, double b)>& evaluator) {
    if (!operand1->hasArgument() && !operand2->hasArgument()) return boost::none;
    return evaluator(operand1->getArgument(), operand2->getArgument());
}

Chrysalis::BinaryFunctionArgument::BinaryFunctionArgument(const num* operand1, const num* operand2,
                                                          boost::optional<double>(BinaryFunction::*function)(const num* operand1, const num* operand2))
        : NumberArgument([&] {
            return (evaluator.*function)(operand1, operand2);
        }()), operand1_(operand1), operand2_(operand2), function_(function) {
}

Chrysalis::BinaryFunctionArgument::~BinaryFunctionArgument() {
    delete operand1_;
    delete operand2_;
}
