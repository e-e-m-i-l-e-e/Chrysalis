#include "instructions/IntersectionPointInstruction.h"

using namespace Chrysalis;

IntersectionPointInstruction::IntersectionPointInstruction(ProjectSpace* space, SelectedPatternsArgument* patterns,
                                                           const name* pointName,
                                                           const name* pointFrom1, const name* pointTo1,
                                                           const name* pointFrom2, const name* pointTo2)
    : BasePatternInstruction(space, patterns), pointName_(pointName), pointFrom1_(pointFrom1), pointTo1_(pointTo1),
                                               pointFrom2_(pointFrom2), pointTo2_(pointTo2) {}

IntersectionPointInstruction::~IntersectionPointInstruction() {
    delete pointFrom1_;
    delete pointTo1_;
    delete pointFrom2_;
    delete pointTo2_;
}

bool IntersectionPointInstruction::isValid() {
    return pointFrom1_->hasArgument() && eachPatternHasPoint(pointFrom1_->getArgument()) &&
           pointFrom2_->hasArgument() && eachPatternHasPoint(pointFrom2_->getArgument()) &&
           pointTo1_->hasArgument() && eachPatternHasPoint(pointTo1_->getArgument()) &&
           pointTo2_->hasArgument() && eachPatternHasPoint(pointTo2_->getArgument()) &&
           pointName_->hasArgument();
}

void IntersectionPointInstruction::execute() {
    const auto intersection = ProjectSpace::intersection(
        CGAL::Line(*anyPattern()->getPoint(pointFrom1_->getArgument()), *anyPattern()->getPoint(pointTo1_->getArgument())),
        CGAL::Line(*anyPattern()->getPoint(pointFrom2_->getArgument()), *anyPattern()->getPoint(pointTo2_->getArgument()))
    );
    if (intersection) {
        for (const auto pattern: patterns()) {
            pattern->addPoint(pointName_->getArgument(), space().addPoint(intersection.value()));
        }
    }
}
