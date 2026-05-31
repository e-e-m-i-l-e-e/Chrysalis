#include "FreePointInstruction.h"

using namespace Chrysalis;

FreePointInstruction::FreePointInstruction(ProjectSpace* space, Argument<PatternSpacesArgument*>* patternSpaces,
                                           Argument<std::string>* pointName, Argument<double>* x, Argument<double>* y)
    : BasePatternSpacesInstruction(space, patternSpaces), pointName_(pointName), x_(x), y_(y) {
    pointName_->addObserver(this);
    x_->addObserver(this);
    y_->addObserver(this);
}

FreePointInstruction::~FreePointInstruction() {
    delete pointName_;
    delete x_;
    delete y_;
}

bool FreePointInstruction::isValid() {
    return pointName_->hasArgument() && x_->hasArgument() && y_->hasArgument();
}

void FreePointInstruction::reset()
{
}

void FreePointInstruction::execute() {
    const auto point = space_->addPoint(x_->getArgument(), y_->getArgument());
    for (const auto& patternSpace: *patternSpaces_->getArgument()) {
        patternSpace->addPoint(pointName_->getArgument(), point);
    }
}
