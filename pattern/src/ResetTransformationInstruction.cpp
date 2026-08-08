#include "instructions/ResetTransformationInstruction.h"

using namespace Chrysalis;

ResetTransformationInstruction::ResetTransformationInstruction(ProjectSpace* space, args::patterns* patterns)
    : BasePatternInstruction(space, patterns) {}

bool ResetTransformationInstruction::isValid() {
    return true;
}

void ResetTransformationInstruction::execute() {
    for (const auto pattern: *patterns_) {
        pattern->transform(Transformation(nullptr, {0, 0}, 0));
    }
}
