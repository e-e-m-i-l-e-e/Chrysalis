#include "arguments/BinaryFunctionArgument.h"

using namespace Chrysalis;

BinaryFunctionArgument::BinaryFunctionArgument(args::number&& operand1, args::number&& operand2)
    : operand1_(std::move(operand1)), operand2_(std::move(operand2)) {}

std::expected<double, Error> BinaryFunctionArgument::calculate() const {
    return operand1_->get().and_then([this](const double a) {
        return operand2_->get().and_then([this, &a](const double b) {
            return evaluate(a, b);
        });
    });
}

std::expected<double, Error> BinaryFunctionArgument::Add::evaluate(const double a, const double b) const {
    return a + b;
}

std::expected<double, Error> BinaryFunctionArgument::Subtract::evaluate(const double a, const double b) const {
    return a - b;
}

std::expected<double, Error> BinaryFunctionArgument::Multiply::evaluate(const double a, const double b) const {
    return a * b;
}

std::expected<double, Error> BinaryFunctionArgument::Divide::evaluate(const double a, const double b) const {
    return a / b;
}

std::expected<double, Error> BinaryFunctionArgument::Min::evaluate(const double a, const double b) const {
    return a < b ? a : b;
}

std::expected<double, Error> BinaryFunctionArgument::Max::evaluate(const double a, const double b) const {
    return a > b ? a : b;
}