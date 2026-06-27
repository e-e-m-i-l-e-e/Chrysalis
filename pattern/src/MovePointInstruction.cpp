#include "instructions/MovePointInstruction.h"

Chrysalis::MovePointInstruction::MovePointInstruction(ProjectSpace* space, args::patterns* patterns,
                                                      const args::name* pointName, const args::number* angle, const args::number* length)
    : BasePatternInstruction(space, patterns), pointName_(pointName), angle_(angle), length_(length) {}

bool Chrysalis::MovePointInstruction::isValid() {
    return pointName_->isValid() && patterns_->all(&PatternSpace::hasPoint, pointName_->get()) &&
           angle_->isValid() && length_->isValid();
}

void Chrysalis::MovePointInstruction::execute() {
    const Point* point = patterns_->onAny(&PatternSpace::getPoint, pointName_->get());
    space().movePoint(point, ProjectSpace::relativePoint(*point, angle_->get(), length_->get()));
}
