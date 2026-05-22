#include "BinaryFunction.h"

double BinaryFunction::ADDITION(const double a, const double b) {
    return a + b;
}

double BinaryFunction::SUBTRACTION(const double a, const double b) {
    return a - b;
}

double BinaryFunction::MULTIPLICATION(const double a, const double b) {
    return a * b;
}

double BinaryFunction::DIVISION(const double a, const double b) {
    return a / b;
}

double BinaryFunction::MIN(const double a, const double b) {
    return a < b ? a : b;
}

double BinaryFunction::MAX(const double a, const double b) {
    return a > b ? a : b;
}

BinaryFunction::BinaryFunction(BaseArgument* argumentLeft,
                               BaseArgument* argumentRight,
                               double (*function)(double a, double b))
    : argumentLeft(argumentLeft), argumentRight(argumentRight), function(function) {}

double BinaryFunction::getValue() const {
    return (*function)(argumentLeft->getValue(), argumentRight->getValue());
}
