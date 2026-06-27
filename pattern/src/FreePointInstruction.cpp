#include "instructions/FreePointInstruction.h"

using namespace Chrysalis;

FreePointInstruction::FreePointInstruction(ProjectSpace* space, SelectedPatternsArgument* patterns,
                                           const name* pointName, const num* x, const num* y)
    : BasePatternInstruction(space, patterns), pointName_(pointName), x_(x), y_(y) {}

FreePointInstruction::~FreePointInstruction() {
    delete pointName_;
    delete x_;
    delete y_;
}

bool FreePointInstruction::isValid() {
    return pointName_->isValid() && x_->isValid() && y_->isValid();
}

void FreePointInstruction::execute() {
    const auto point = space().addPoint(x_->get(), y_->get());
    for (const auto& pattern: patterns()) {
        pattern->addPoint(pointName_->get(), point);
    }
}
