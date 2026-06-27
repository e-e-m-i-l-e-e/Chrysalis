#include "arguments/BinaryFunctionArgument.h"

Chrysalis::BinaryFunctionArgument::BinaryFunctionArgument(const num* operand1, const num* operand2,
                                                          const BinaryFunction* function)
    : operand1_(operand1), operand2_(operand2), function_(function) {}

Chrysalis::BinaryFunctionArgument::~BinaryFunctionArgument() {
    delete operand1_;
    delete operand2_;
    delete function_;
}

bool Chrysalis::BinaryFunctionArgument::hasValue() const {
    return operand1_->hasValue() && operand2_->hasValue();
}

double Chrysalis::BinaryFunctionArgument::get() const {
    return function_->evaluate(operand1_, operand2_);
}
