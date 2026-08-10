#include "instructions/ExpressionInstruction.h"
#include <iostream>

using namespace Chrysalis;

ExpressionInstruction::ExpressionInstruction(ExpressionsContainer* expressions, const args::name* name, const args::number* value)
    : expressions_(expressions), name_(name), value_(value) {}

ExpressionInstruction::~ExpressionInstruction() {
    delete name_;
    delete value_;
}

bool ExpressionInstruction::isValid() {
    return value_->isValid();
}

void ExpressionInstruction::execute() {
    if (!expressions_->has(name_->get())) {
        expressions_->add(new Expression(name_->get(), value_));
        value_ = nullptr;
    }
}