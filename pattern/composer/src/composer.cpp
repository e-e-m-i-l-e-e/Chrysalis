#include "composer.h"

#include "arguments/ComparisonArgument.h"

using namespace Chrysalis;

args::number Chrysalis::operator ""_(const long double number) {
    return std::make_unique<const Argument<double>>(static_cast<double>(number));
}

std::unique_ptr<BinaryFunctionArgument> Chrysalis::operator+(args::number&& a, args::number&& b) {
    return std::make_unique<BinaryFunctionArgument::Add>(std::move(a), std::move(b));
}

std::unique_ptr<BinaryFunctionArgument> Chrysalis::operator-(args::number&& a, args::number&& b) {
    return std::make_unique<BinaryFunctionArgument::Subtract>(std::move(a), std::move(b));
}

std::unique_ptr<BinaryFunctionArgument> Chrysalis::operator*(args::number&& a, args::number&& b) {
    return std::make_unique<BinaryFunctionArgument::Multiply>(std::move(a), std::move(b));
}

std::unique_ptr<BinaryFunctionArgument> Chrysalis::operator/(args::number&& a, args::number&& b) {
    return std::make_unique<BinaryFunctionArgument::Divide>(std::move(a), std::move(b));
}

std::unique_ptr<BinaryFunctionArgument> Chrysalis::operator+(args::number&& a, const double b) {
    return std::make_unique<BinaryFunctionArgument::Add>(std::move(a), std::make_unique<const Argument<double>>(b));
}

std::unique_ptr<BinaryFunctionArgument> Chrysalis::operator-(args::number&& a, const double b) {
    return std::make_unique<BinaryFunctionArgument::Subtract>(std::move(a), std::make_unique<const Argument<double>>(b));
}

std::unique_ptr<BinaryFunctionArgument> Chrysalis::operator*(args::number&& a, const double b) {
    return std::make_unique<BinaryFunctionArgument::Multiply>(std::move(a), std::make_unique<const Argument<double>>(b));
}

std::unique_ptr<BinaryFunctionArgument> Chrysalis::operator/(args::number&& a, const double b) {
    return std::make_unique<BinaryFunctionArgument::Divide>(std::move(a), std::make_unique<const Argument<double>>(b));
}

std::unique_ptr<BinaryFunctionArgument> Chrysalis::operator+(const double a, args::number&& b) {
    return std::make_unique<BinaryFunctionArgument::Add>(std::make_unique<const Argument<double>>(a), std::move(b));
}

std::unique_ptr<BinaryFunctionArgument> Chrysalis::operator-(const double a, args::number&& b) {
    return std::make_unique<BinaryFunctionArgument::Subtract>(std::make_unique<const Argument<double>>(a), std::move(b));
}

std::unique_ptr<BinaryFunctionArgument> Chrysalis::operator*(const double a, args::number&& b) {
    return std::make_unique<BinaryFunctionArgument::Multiply>(std::make_unique<const Argument<double>>(a), std::move(b));
}

std::unique_ptr<BinaryFunctionArgument> Chrysalis::operator/(const double a, args::number&& b) {
    return std::make_unique<BinaryFunctionArgument::Divide>(std::make_unique<const Argument<double>>(a), std::move(b));
}

const args::condition* Chrysalis::operator<(args::number&& a, args::number&& b) {
    return new args::compare::Less(std::move(a), std::move(b));
}
