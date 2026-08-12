#include "instructions/TransformInstruction.h"

using namespace Chrysalis;

TransformInstruction::TransformInstruction(ProjectSpace* space, args::patterns* patterns,
                                           const args::vector* from, const args::vector* to)
    : BasePatternInstruction(space, patterns), from_(from), to_(to) {}

TransformInstruction::~TransformInstruction() {
    delete from_;
    delete to_;
}

void TransformInstruction::execute() {
    for (const auto pattern: *patterns_) {
        pattern->transform(Transformation(from_->origin()->get(), *to_->origin()->get() - *from_->origin()->get(), to_->angle()->get().value() - from_->angle()->get().value()));
    }
}
