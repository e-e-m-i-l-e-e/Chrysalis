#include "instructions/IntersectionPointInstruction.h"

using namespace Chrysalis;

IntersectionPointInstruction::IntersectionPointInstruction(ProjectSpace* space, args::patterns* patterns,
                                                           const args::name* pointName,
                                                           const args::name* pointFrom1, const args::name* pointTo1,
                                                           const args::name* pointFrom2, const args::name* pointTo2)
    : BasePatternInstruction(space, patterns), pointName_(pointName), pointFrom1_(pointFrom1), pointTo1_(pointTo1),
                                               pointFrom2_(pointFrom2), pointTo2_(pointTo2) {}

IntersectionPointInstruction::~IntersectionPointInstruction() {
    delete pointFrom1_;
    delete pointTo1_;
    delete pointFrom2_;
    delete pointTo2_;
}

bool IntersectionPointInstruction::isValid() {
    return pointFrom1_->isValid() && patterns_->all(&PatternSpace::hasPoint, pointFrom1_->get()) &&
           pointFrom2_->isValid() && patterns_->all(&PatternSpace::hasPoint, pointFrom2_->get()) &&
           pointTo1_->isValid() && patterns_->all(&PatternSpace::hasPoint, pointTo1_->get()) &&
           pointTo2_->isValid() && patterns_->all(&PatternSpace::hasPoint, pointTo2_->get()) &&
           pointName_->isValid();
}

void IntersectionPointInstruction::execute() {
    const auto intersection = ProjectSpace::intersection(
        CGAL::Line(*patterns_->onAny(&PatternSpace::getPoint, pointFrom1_->get()), *patterns_->onAny(&PatternSpace::getPoint, pointTo1_->get())),
        CGAL::Line(*patterns_->onAny(&PatternSpace::getPoint, pointFrom2_->get()), *patterns_->onAny(&PatternSpace::getPoint, pointTo2_->get()))
    );
    if (intersection) {
        for (const auto pattern: *patterns_) {
            pattern->addPoint(pointName_->get(), space().addPoint(intersection.value()));
        }
    }
}
