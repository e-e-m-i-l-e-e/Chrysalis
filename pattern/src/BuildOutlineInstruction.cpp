#include "instructions/BuildOutlineInstruction.h"

#include "Outline.h"

using namespace Chrysalis;

BuildOutlineInstruction::BuildOutlineInstruction(ProjectSpace* space, args::patterns* selectedPatterns,
                                                 args::name&& outlineName, const args::container<const PatternPointArgument>* points)
    : BasePatternInstruction(space, selectedPatterns), outlineName_(std::move(outlineName)), points_(points) {}

BuildOutlineInstruction::~BuildOutlineInstruction() {
    delete points_;
}

void BuildOutlineInstruction::execute() {
    if (const auto name = outlineName_->get()) {
        for (const auto& pattern: *patterns_) {
            Outline* outline;
            if (!pattern->getOutline()->has(name.value())) {
                outline = new Outline(name.value());
                pattern->getOutline()->add(outline);
            } else outline = pattern->getOutline()->get(name.value());
            for (const auto& point: *points_) {
                outline->add(point->get());
                pattern->shape::notify(&PatternShapeObserver::pointAdded, outline, point->get());
            }
        }
    }
}