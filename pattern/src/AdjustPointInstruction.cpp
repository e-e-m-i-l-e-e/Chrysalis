#include "instructions/AdjustPointInstruction.h"

Chrysalis::AdjustPointInstruction::AdjustPointInstruction(ProjectSpace* space, args::patterns* patterns,
                                                          const args::point* target,
                                                          const args::vector* vector1, const args::vector* vector2)
    : BasePatternInstruction(space, patterns), target_(target), vector1_(vector1), vector2_(vector2) {}

Chrysalis::AdjustPointInstruction::~AdjustPointInstruction() {
    delete target_;
    delete vector1_;
    delete vector2_;
}

bool Chrysalis::AdjustPointInstruction::isValid() {
    return target_->isValid() && vector1_->isValid() && vector2_->isValid();
}

void Chrysalis::AdjustPointInstruction::execute() {
    space().movePoint(target_->get(), CG::circlesIntersection(
        *target_->get(),
        *vector1_->origin()->get(), vector1_->length()->get(),
        *vector2_->origin()->get(), vector2_->length()->get()
    ));
}
