#include "instructions/ExpressionInstruction.h"
#include <iostream>

using namespace Chrysalis;

ExpressionInstruction::ExpressionInstruction(ExpressionsContainer* expressions, args::name&& name, args::number&& value)
    : expressions_(expressions), name_(std::move(name)), value_(std::move(value)) {}

void ExpressionInstruction::execute() {
    if (const auto name = name_->get()) {
        if (!expressions_->has(name.value())) {
            expressions_->add(new Expression(name.value(), std::move(value_)));
        }
    }
}