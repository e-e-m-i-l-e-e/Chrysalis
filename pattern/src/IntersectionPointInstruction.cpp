#include "instructions/IntersectionPointInstruction.h"

#include <ranges>

#include "arguments/SegmentArgument.h"

using namespace Chrysalis;

IntersectionPointInstruction::IntersectionPointInstruction(ProjectSpace* space, args::patterns* patterns,
                                                           const args::line* line,
                                                           const args::container<args::name>* names,
                                                           const args::container<args::line>* targets)
    : BasePatternInstruction(space, patterns), line_(line), names_(names), targets_(targets) {}

IntersectionPointInstruction::~IntersectionPointInstruction() {
    delete line_;
    delete names_;
    delete targets_;
}

bool IntersectionPointInstruction::isValid() {
    return line_->isValid();
}

void IntersectionPointInstruction::execute() {
    if (dynamic_cast<const args::segment*>(line_)) {

    } else if (dynamic_cast<const args::vector*>(line_)) {

    } else if (dynamic_cast<const args::ray*>(line_)) {

    } else {
    }
    for (auto [name, otherLine] : std::views::zip(*names_, *targets_)) {
        boost::optional<CGAL::Point> intersection;
        if (const auto vector = dynamic_cast<const args::vector*>(otherLine)) {
            intersection = ProjectSpace::intersection(static_cast<CGAL::Line>(*line_), static_cast<CGAL::Segment>(*vector));
        } else if (const auto ray = dynamic_cast<const args::ray*>(otherLine)) {
            intersection = ProjectSpace::intersection(static_cast<CGAL::Line>(*line_), static_cast<CGAL::Ray>(*ray));
        } else {
            intersection = ProjectSpace::intersection(static_cast<CGAL::Line>(*line_), static_cast<CGAL::Line>(*otherLine));
        }
        if (intersection) {
            for (const auto pattern : *patterns_) {
                pattern->addPoint(name->get(), space().addPoint(*intersection));
            }
        }
    }
}
