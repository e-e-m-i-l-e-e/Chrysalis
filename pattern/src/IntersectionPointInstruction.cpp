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
    return pointFrom1_->isValid() && eachPatternHasPoint(pointFrom1_->get()) &&
           pointFrom2_->isValid() && eachPatternHasPoint(pointFrom2_->get()) &&
           pointTo1_->isValid() && eachPatternHasPoint(pointTo1_->get()) &&
           pointTo2_->isValid() && eachPatternHasPoint(pointTo2_->get()) &&
           pointName_->isValid();
}

void IntersectionPointInstruction::execute() {
    const auto intersection = ProjectSpace::intersection(
        CGAL::Line(*anyPattern()->getPoint(pointFrom1_->get()), *anyPattern()->getPoint(pointTo1_->get())),
        CGAL::Line(*anyPattern()->getPoint(pointFrom2_->get()), *anyPattern()->getPoint(pointTo2_->get()))
    );
    if (intersection) {
        for (const auto pattern: patterns()) {
            pattern->addPoint(pointName_->get(), space().addPoint(intersection.value()));
        }
    }
}
