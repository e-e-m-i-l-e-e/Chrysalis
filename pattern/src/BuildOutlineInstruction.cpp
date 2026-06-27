#include "instructions/BuildOutlineInstruction.h"

#include "Outline.h"

using namespace Chrysalis;

BuildOutlineInstruction::BuildOutlineInstruction(ProjectSpace* space, SelectedPatternsArgument* selectedPatterns,
                                                 name* outlineName, name* point)
    : BasePatternInstruction(space, selectedPatterns), outlineName_(outlineName), point_(point) {}

BuildOutlineInstruction::~BuildOutlineInstruction() {
    delete outlineName_;
    delete point_;
}

bool BuildOutlineInstruction::isValid() {
    return point_->hasValue();
}

void BuildOutlineInstruction::execute() {
    for (const auto& pattern: patterns()) {
        if (!pattern->hasPoint(point_->get())) return;
    }
    for (const auto& pattern: patterns()) {
        const auto& pointName = point_->get();
        const auto& name = outlineName_->hasValue() ? outlineName_->get() : Outline::DEFAULT;
        const auto& outline = pattern->getOutline();
        if (outline->has(name)) outline->get(name)->addPoint(pointName);
        else outline->add(new Outline(name, pointName));
    }
}