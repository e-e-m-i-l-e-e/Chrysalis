#include "arguments/ConditionalArgument.h"

using namespace Chrysalis;

ConditionalArgument::ConditionalArgument(const args::condition* condition, args::number&& positive,
                                         args::number&& negative)
    : condition_(condition), positive_(std::move(positive)), negative_(std::move(negative)) {}

ConditionalArgument::~ConditionalArgument() {
    delete condition_;
}

std::expected<double, Error> ConditionalArgument::calculate() const {
    return condition_->get().and_then([this](const bool condition) {
        const auto& result = condition ? positive_ : negative_;
        return result.get()->get();
    });
}
