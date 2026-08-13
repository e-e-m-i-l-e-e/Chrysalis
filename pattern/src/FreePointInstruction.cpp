#include "instructions/FreePointInstruction.h"

using namespace Chrysalis;

FreePointInstruction::FreePointInstruction(ProjectSpace* space, args::patterns* patterns,
                                           args::name&& pointName, args::number&& x, args::number&& y)
    : BasePatternInstruction(space, patterns), pointName_(std::move(pointName)), x_(std::move(x)), y_(std::move(y)) {}

void FreePointInstruction::execute() {
    const auto pointName = pointName_->get();
    const auto x = x_->get();
    const auto y = y_->get();

    if (!pointName.has_value() || !x.has_value() || !y.has_value()) return;

    const auto point = space().addPoint(x.value(), y.value());
    for (const auto& pattern: *patterns_) {
        pattern->addPoint(pointName.value(), point);
    }
}
