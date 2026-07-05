#include "arguments/ConditionalArgument.h"

using namespace Chrysalis;

ConditionalArgument::ConditionalArgument(const args::condition* condition, const args::number* positive,
                                         const args::number* negative)
    : condition_(condition), positive_(positive), negative_(negative) {}

ConditionalArgument::~ConditionalArgument() {
    delete condition_;
    delete positive_;
    delete negative_;
}

bool ConditionalArgument::isValid() const {
    return condition_->isValid() && positive_->isValid() && negative_->isValid();
}

double ConditionalArgument::calculate() const {
    return condition_->get() ? positive_->get() : negative_->get();
}
