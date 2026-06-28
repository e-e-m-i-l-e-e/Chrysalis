#include "instructions/BuildOutlineInstruction.h"

#include "Outline.h"

using namespace Chrysalis;

BuildOutlineInstruction::BuildOutlineInstruction(ProjectSpace* space, args::patterns* selectedPatterns,
                                                 args::optional<args::name>* outlineName, args::name* point)
    : BasePatternInstruction(space, selectedPatterns), outlineName_(outlineName), point_(point) {}

BuildOutlineInstruction::~BuildOutlineInstruction() {
    delete outlineName_;
    delete point_;
}

bool BuildOutlineInstruction::isValid() {
    return point_->isValid();
}

void BuildOutlineInstruction::execute() {
    if (!patterns_->all(&PatternSpace::hasPoint, point_->get())) return;
    for (const auto& pattern: *patterns_) {
        const auto& pointName = point_->get();
        const auto& name = outlineName_->argument() ? outlineName_->argument()->get() : Outline::DEFAULT;
        if (const auto& outline = pattern->getOutline(); outline->has(name)) outline->get(name)->addPoint(pointName);
        else outline->add(new Outline(name, pointName));
    }
}