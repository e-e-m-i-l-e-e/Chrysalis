#include "Expression.h"

using namespace Chrysalis;

ExpressionValue::operator double() const {
    return value;
}

Expression::Expression(const std::string& name, args::number&& expression)
    : BaseNamedElement(name), expression_(std::move(expression)) {}

std::expected<ExpressionValue, Error> Expression::calculate() const {
    return expression_->get().transform([](const double value) {
        return ExpressionValue{value};
    });
}