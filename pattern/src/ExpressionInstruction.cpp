#include "instructions/ExpressionInstruction.h"

Chrysalis::ExpressionInstruction::ExpressionInstruction(ExpressionsContainer* expressions, args::expr* expression)
    : expressions_(expressions), expression_(expression) {}

bool Chrysalis::ExpressionInstruction::isValid() {
    return expression_->isValid();
}

void Chrysalis::ExpressionInstruction::execute() {
    if (!expressions_->has(expression_->getName())) expressions_->add(expression_);
}
