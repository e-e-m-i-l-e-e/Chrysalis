#include "arguments/BinaryFunctionArgument.h"

using namespace Chrysalis;

BinaryFunctionArgument::BinaryFunctionArgument(const args::number* operand1, const args::number* operand2)
    : operand1_(operand1), operand2_(operand2) {}

BinaryFunctionArgument::~BinaryFunctionArgument() {
    delete operand1_;
    delete operand2_;
}

bool BinaryFunctionArgument::isValid() const {
    return operand1_->isValid() && operand2_->isValid();
}

double BinaryFunctionArgument::calculate() const {
    return evaluate(operand1_->get(), operand2_->get());
}

double BinaryFunctionArgument::Add::evaluate(const double a, const double b) const {
    return a + b;
}

double BinaryFunctionArgument::Subtract::evaluate(const double a, const double b) const {
    return a - b;
}

double BinaryFunctionArgument::Multiply::evaluate(const double a, const double b) const {
    return a * b;
}

double BinaryFunctionArgument::Divide::evaluate(const double a, const double b) const {
    return a / b;
}

double BinaryFunctionArgument::Min::evaluate(const double a, const double b) const {
    return a < b ? a : b;
}

double BinaryFunctionArgument::Max::evaluate(const double a, const double b) const {
    return a > b ? a : b;
}