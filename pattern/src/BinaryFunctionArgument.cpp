#include "BinaryFunctionArgument.h"

double BinaryFunctionArgument::Use::ADDITION(const double a, const double b) {
    return a + b;
}

double BinaryFunctionArgument::Use::SUBTRACTION(const double a, const double b) {
    return a - b;
}

double BinaryFunctionArgument::Use::MULTIPLICATION(const double a, const double b) {
    return a * b;
}

double BinaryFunctionArgument::Use::DIVISION(const double a, const double b) {
    return a / b;
}

double BinaryFunctionArgument::Use::MIN(const double a, const double b) {
    return a < b ? a : b;
}

double BinaryFunctionArgument::Use::MAX(const double a, const double b) {
    return a > b ? a : b;
}

BinaryFunctionArgument::BinaryFunctionArgument(Argument* argumentLeft,
                               Argument* argumentRight,
                               double (*function)(double a, double b))
    : argumentLeft(argumentLeft), argumentRight(argumentRight), function(function) {
    argument_ = (*function)(argumentLeft->getArgument(), argumentRight->getArgument());
}

BinaryFunctionArgument::~BinaryFunctionArgument() {
    delete argumentLeft;
    delete argumentRight;
}
