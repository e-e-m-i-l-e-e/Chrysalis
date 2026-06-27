#include "instructions/MovePointInstruction.h"

Chrysalis::MovePointInstruction::MovePointInstruction(ProjectSpace* space, SelectedPatternsArgument* patterns,
                                                      const name* pointName, const num* angle, const num* length)
    : BasePatternInstruction(space, patterns), pointName_(pointName), angle_(angle), length_(length) {}

bool Chrysalis::MovePointInstruction::isValid() {
    return pointName_->isValid() && eachPatternHasPoint(pointName_->get()) &&
           angle_->isValid() && length_->isValid();
}

void Chrysalis::MovePointInstruction::execute() {
    const Point* point = anyPattern()->getPoint(pointName_->get());
    space().movePoint(point, ProjectSpace::relativePoint(*point, angle_->get(), length_->get()));
}
