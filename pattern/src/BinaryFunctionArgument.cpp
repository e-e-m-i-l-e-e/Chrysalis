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

const BinaryFunctionArgument* Chrysalis::operator+(const args::number& operand1, const args::number& operand2) {
    return new BinaryFunctionArgument::Add(&operand1, &operand2);
}

const BinaryFunctionArgument* Chrysalis::operator-(const args::number& operand1, const args::number& operand2) {
    return new BinaryFunctionArgument::Subtract(&operand1, &operand2);
}

const BinaryFunctionArgument* Chrysalis::operator*(const args::number& operand1, const args::number& operand2) {
    return new BinaryFunctionArgument::Multiply(&operand1, &operand2);
}

const BinaryFunctionArgument* Chrysalis::operator/(const args::number& operand1, const args::number& operand2) {
    return new BinaryFunctionArgument::Divide(&operand1, &operand2);
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