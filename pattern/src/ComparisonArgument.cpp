#include "arguments/ComparisonArgument.h"

using namespace Chrysalis;

ComparisonArgument::ComparisonArgument(args::number&& value1, args::number&& value2)
    : value1_(std::move(value1)), value2_(std::move(value2)) {}

std::expected<bool, Error> ComparisonArgument::calculate() const {
    return value1_.get()->get().and_then([this](const bool value1) {
        return value2_.get()->get().transform([this, value1](const bool value2) {
            return evaluate(value1, value2);
        });
    });
}

bool ComparisonArgument::Equal::evaluate(const double a, const double b) const {
    return a == b;
}

bool ComparisonArgument::NotEqual::evaluate(const double a, const double b) const {
    return a != b;
}

bool ComparisonArgument::Greater::evaluate(const double a, const double b) const {
    return a > b;
}

bool ComparisonArgument::GreaterEqual::evaluate(const double a, const double b) const {
    return a >= b;
}

bool ComparisonArgument::Less::evaluate(const double a, const double b) const {
    return a < b;
}

bool ComparisonArgument::LessEqual::evaluate(const double a, const double b) const {
    return a <= b;
}
