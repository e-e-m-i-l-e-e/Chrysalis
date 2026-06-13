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
    return pointName_->hasArgument() && x_->hasArgument() && y_->hasArgument();
}

void FreePointInstruction::execute() {
    const auto point = space().addPoint(x_->getArgument(), y_->getArgument());
    for (const auto& pattern: patterns()) {
        pattern->addPoint(pointName_->getArgument(), point);
        pattern->notify(&PatternSpaceObserver::pointAdded, point);
    }
}
