#include "instructions/MovePointInstruction.h"

Chrysalis::MovePointInstruction::MovePointInstruction(ProjectSpace* space, args::patterns* patterns,
                                                          const PatternPointArgument* point,
                                                          const args::vector* vector1,
                                                          const args::optional<args::vector>* vector2)
    : BasePatternInstruction(space, patterns), point_(point), vector1_(vector1), vector2_(vector2) {}

Chrysalis::MovePointInstruction::~MovePointInstruction() {
    delete point_;
    delete vector1_;
    delete vector2_;
}

bool Chrysalis::MovePointInstruction::isValid() {
    return point_->isValid() && vector1_->isValid();
}

void Chrysalis::MovePointInstruction::execute() {
    if (vector2_->hasArgument()) {
        space().movePoint(point_->get(), CG::circlesIntersection(
                              *point_->get(),
                              *vector1_->origin()->get(), vector1_->length()->get(),
                              *vector2_->argument()->origin()->get(), vector2_->argument()->length()->get()
                          ));
    } else {
        space().movePoint(point_->get(), CG::relativePoint(*point_->get(), vector1_->angle()->get(), vector1_->length()->get()));
    }
}
