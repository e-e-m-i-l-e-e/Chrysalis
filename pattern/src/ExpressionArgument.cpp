#include "arguments/ExpressionArgument.h"

using namespace Chrysalis;

ExpressionArgument::ExpressionArgument(const ExpressionsContainer* expressions, const args::name* name)
    : expressions_(expressions), name_(name) {}

ExpressionArgument::~ExpressionArgument() {
    delete name_;
}

bool ExpressionArgument::isValid() const {
    return expressions_->has(name_->get());
}

double ExpressionArgument::calculate() const {
    return expressions_->get(name_->get())->get();
}
