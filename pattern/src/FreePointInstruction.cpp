#include "instructions/FreePointInstruction.h"

using namespace Chrysalis;

FreePointInstruction::FreePointInstruction(ProjectSpace* space, args::patterns* patterns,
                                           const args::name* pointName, args::number&& x, args::number&& y)
    : BasePatternInstruction(space, patterns), pointName_(pointName), x_(std::move(x)), y_(std::move(y)) {}

FreePointInstruction::~FreePointInstruction() {
    delete pointName_;
}

void FreePointInstruction::execute() {
    const auto point = space().addPoint(x_->get().value(), y_->get().value());
    for (const auto& pattern: *patterns_) {
        pattern->addPoint(pointName_->get().value(), point);
    }
}
