#include "instructions/MovePointInstruction.h"

Chrysalis::MovePointInstruction::MovePointInstruction(ProjectSpace* space, args::patterns* patterns,
                                                      const args::vector* vector)
    : BasePatternInstruction(space, patterns), vector_(vector) {}

bool Chrysalis::MovePointInstruction::isValid() {
    return vector_->isValid();
}

void Chrysalis::MovePointInstruction::execute() {
    const Point* point = vector_->origin()->get();
    space().movePoint(point, CG::relativePoint(*point, vector_->angle()->get(), vector_->length()->get()));
}
