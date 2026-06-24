#include "instructions/MovePointInstruction.h"

Chrysalis::MovePointInstruction::MovePointInstruction(ProjectSpace* space, SelectedPatternsArgument* patterns,
                                                      const name* pointName, const num* angle, const num* length)
    : BasePatternInstruction(space, patterns), pointName_(pointName), angle_(angle), length_(length) {}

bool Chrysalis::MovePointInstruction::isValid() {
    return pointName_->hasArgument() && eachPatternHasPoint(pointName_->getArgument()) &&
           angle_->hasArgument() && length_->hasArgument();
}

void Chrysalis::MovePointInstruction::execute() {
    const Point* point = anyPattern()->getPoint(pointName_->getArgument());
    space().movePoint(point, ProjectSpace::relativePoint(*point, angle_->getArgument(), length_->getArgument()));
}
