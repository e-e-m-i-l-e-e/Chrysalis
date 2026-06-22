#include "arguments/BinaryFunctionArgument.h"

Chrysalis::BinaryFunctionArgument::BinaryFunctionArgument(const num* operand1, const num* operand2,
                                                          const BinaryFunction* function)
    : NumberArgument(function->evaluate(operand1, operand2)),
      operand1_(operand1), operand2_(operand2), function_(function) {}

Chrysalis::BinaryFunctionArgument::~BinaryFunctionArgument() {
    delete operand1_;
    delete operand2_;
    delete function_;
}