#include "instructions/BuildOutlineInstruction.h"

#include "Outline.h"

using namespace Chrysalis;

BuildOutlineInstruction::BuildOutlineInstruction(ProjectSpace* space, args::patterns* selectedPatterns,
                                                 const args::name* outlineName, const PatternPointArgument* point)
    : BasePatternInstruction(space, selectedPatterns), outlineName_(outlineName), point_(point) {}

BuildOutlineInstruction::~BuildOutlineInstruction() {
    delete outlineName_;
    delete point_;
}

bool BuildOutlineInstruction::isValid() {
    return point_->isValid();
}

void BuildOutlineInstruction::execute() {
    for (const auto& pattern: *patterns_) {
        const auto& point = point_->get();
        const auto& name = outlineName_->get();
        pattern->getOutline()->get(name)->add(point);
    }
}