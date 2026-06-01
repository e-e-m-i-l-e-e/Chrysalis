#include "FreePointInstruction.h"

using namespace Chrysalis;

FreePointInstruction::FreePointInstruction(ProjectSpace* space, Argument<PatternSpacesArgument*>* patternSpaces,
                                           name* pointName, num* x, num* y)
    : BasePatternInstruction(space, patternSpaces), pointName_(pointName), x_(x), y_(y) {}

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
    for (const auto& patternSpace: patterns()) {
        patternSpace->addPoint(pointName_->getArgument(), point);
    }
}
