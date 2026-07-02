#include "instructions/AdjustPointInstruction.h"

Chrysalis::AdjustPointInstruction::AdjustPointInstruction(ProjectSpace* space, args::patterns* patterns,
                                                          const args::point* target,
                                                          const args::point* point1, const args::number* length1,
                                                          const args::point* point2, const args::number* length2)
    : BasePatternInstruction(space, patterns), target_(target), point1_(point1), length1_(length1),
      point2_(point2), length2_(length2) {}

Chrysalis::AdjustPointInstruction::~AdjustPointInstruction() {
    delete target_;
    delete point1_;
    delete length1_;
    delete point2_;
    delete length2_;
}

bool Chrysalis::AdjustPointInstruction::isValid() {
    return target_->isValid() &&
        point1_->isValid() && length1_->isValid() &&
        point2_->isValid() && length2_->isValid();
}

void Chrysalis::AdjustPointInstruction::execute() {
    space().movePoint(target_->get(), CG::circlesIntersection(
        *target_->get(),
        *point1_->get(), length1_->get(),
        *point2_->get(), length2_->get()
    ));
}
