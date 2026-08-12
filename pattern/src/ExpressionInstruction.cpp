#include "instructions/ExpressionInstruction.h"
#include <iostream>

using namespace Chrysalis;

ExpressionInstruction::ExpressionInstruction(ExpressionsContainer* expressions, const args::name* name, args::number&& value)
    : expressions_(expressions), name_(name), value_(std::move(value)) {}

ExpressionInstruction::~ExpressionInstruction() {
    delete name_;
}

void ExpressionInstruction::execute() {
    if (const auto name = name_->get()) {
        if (!expressions_->has(name.value())) {
            expressions_->add(new Expression(name.value(), std::move(value_)));
        }
    }
}