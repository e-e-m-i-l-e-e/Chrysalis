#include "Expression.h"

using namespace Chrysalis;

ExpressionValue::operator double() const {
    return value;
}

Expression::Expression(const std::string& name, const args::number* expression)
    : BaseNamedElement(name), expression_(expression) {}

Expression::~Expression() {
    delete expression_;
}

bool Expression::isValid() const {
    return expression_->isValid();
}

ExpressionValue Expression::calculate() const {
    return {expression_->get()};
}