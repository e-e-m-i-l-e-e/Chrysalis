#include "arguments/ComparisonArgument.h"

Chrysalis::ComparisonArgument::ComparisonArgument(const args::number* value1, const args::number* value2)
    : value1_(value1), value2_(value2) {}

Chrysalis::ComparisonArgument::~ComparisonArgument() {
    delete value1_;
    delete value2_;
}

bool Chrysalis::ComparisonArgument::isValid() const {
    return value1_->isValid() && value2_->isValid();
}

bool Chrysalis::ComparisonArgument::calculate() const {
    return evaluate(value1_->get(), value2_->get());
}

const Chrysalis::ComparisonArgument* Chrysalis::operator==(const args::number& value1, const args::number& value2) {
    return new ComparisonArgument::Equal(&value1, &value2);
}

const Chrysalis::ComparisonArgument* Chrysalis::operator!=(const args::number& value1, const args::number& value2) {
    return new ComparisonArgument::NotEqual(&value1, &value2);
}

const Chrysalis::ComparisonArgument* Chrysalis::operator>(const args::number& value1, const args::number& value2) {
    return new ComparisonArgument::Greater(&value1, &value2);
}

const Chrysalis::ComparisonArgument* Chrysalis::operator>=(const args::number& value1, const args::number& value2) {
    return new ComparisonArgument::GreaterEqual(&value1, &value2);
}

const Chrysalis::ComparisonArgument* Chrysalis::operator<(const args::number& value1, const args::number& value2) {
    return new ComparisonArgument::Less(&value1, &value2);
}

const Chrysalis::ComparisonArgument* Chrysalis::operator<=(const args::number& value1, const args::number& value2) {
    return new ComparisonArgument::LessEqual(&value1, &value2);
}

bool Chrysalis::ComparisonArgument::Equal::evaluate(const double a, const double b) const {
    return a == b;
}

bool Chrysalis::ComparisonArgument::NotEqual::evaluate(const double a, const double b) const {
    return a != b;
}

bool Chrysalis::ComparisonArgument::Greater::evaluate(const double a, const double b) const {
    return a > b;
}

bool Chrysalis::ComparisonArgument::GreaterEqual::evaluate(const double a, const double b) const {
    return a >= b;
}

bool Chrysalis::ComparisonArgument::Less::evaluate(const double a, const double b) const {
    return a < b;
}

bool Chrysalis::ComparisonArgument::LessEqual::evaluate(const double a, const double b) const {
    return a <= b;
}
