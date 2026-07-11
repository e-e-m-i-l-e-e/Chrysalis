#include "composer.h"

#include "arguments/ComparisonArgument.h"

using namespace Chrysalis;

const BinaryFunctionArgument& Chrysalis::operator+(const args::number& operand1, const args::number& operand2) {
    return *new BinaryFunctionArgument::Add(&operand1, &operand2);
}

const BinaryFunctionArgument& Chrysalis::operator-(const args::number& operand1, const args::number& operand2) {
    return *new BinaryFunctionArgument::Subtract(&operand1, &operand2);
}

const BinaryFunctionArgument& Chrysalis::operator*(const args::number& operand1, const args::number& operand2) {
    return *new BinaryFunctionArgument::Multiply(&operand1, &operand2);
}

const BinaryFunctionArgument& Chrysalis::operator/(const args::number& operand1, const args::number& operand2) {
    return *new BinaryFunctionArgument::Divide(&operand1, &operand2);
}

const BinaryFunctionArgument& Chrysalis::operator+(const args::number& a, const double b) {
    return *new BinaryFunctionArgument::Add(&a, new Argument(b));
}

const BinaryFunctionArgument& Chrysalis::operator-(const args::number& a, const double b) {
    return *new BinaryFunctionArgument::Subtract(&a, new Argument(b));
}

const BinaryFunctionArgument& Chrysalis::operator*(const args::number& a, const double b) {
    return *new BinaryFunctionArgument::Multiply(&a, new Argument(b));
}

const BinaryFunctionArgument& Chrysalis::operator/(const args::number& a, const double b) {
    return *new BinaryFunctionArgument::Divide(&a, new Argument(b));
}

const BinaryFunctionArgument& Chrysalis::operator+(const double a, const args::number& b) {
    return *new BinaryFunctionArgument::Add(new Argument(a), &b);
}

const BinaryFunctionArgument& Chrysalis::operator-(const double a, const args::number& b) {
    return *new BinaryFunctionArgument::Subtract(new Argument(a), &b);
}

const BinaryFunctionArgument& Chrysalis::operator*(const double a, const args::number& b) {
    return *new BinaryFunctionArgument::Multiply(new Argument(a), &b);
}

const BinaryFunctionArgument& Chrysalis::operator/(const double a, const args::number& b) {
    return *new BinaryFunctionArgument::Divide(new Argument(a), &b);
}

const args::condition* Chrysalis::operator<(const args::number& a, const args::number& b) {
    return new args::compare::Less(&a, &b);
}
