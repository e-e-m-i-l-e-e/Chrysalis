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

void BuildOutlineInstruction::execute() {
    if (const auto name = outlineName_->get()) {
        for (const auto& pattern: *patterns_) {
            const auto& point = point_->get();
            pattern->getOutline()->get(name.value())->add(point);
        }
    }
}