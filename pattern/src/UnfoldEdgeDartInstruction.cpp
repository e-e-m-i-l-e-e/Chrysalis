#include "instructions/UnfoldEdgeDartInstruction.h"

using namespace Chrysalis;

UnfoldEdgeDartInstruction::UnfoldEdgeDartInstruction(ProjectSpace* space, args::patterns* patterns,
                                                     const args::name* edgePointFrom, const args::name* edgePointTo,
                                                     const args::name* apexPoint, const args::name* leg1Point, const args::number* intake)
    : BasePatternInstruction(space, patterns), edgePointFrom_(edgePointFrom), edgePointTo_(edgePointTo),
      apexPoint_(apexPoint), leg1Point_(leg1Point), intake_(intake) {}

UnfoldEdgeDartInstruction::~UnfoldEdgeDartInstruction() {
    delete edgePointFrom_;
    delete edgePointTo_;
    delete apexPoint_;
    delete leg1Point_;
    delete intake_;
}

bool UnfoldEdgeDartInstruction::isValid() {
    return edgePointFrom_->isValid() && patterns_->all(&PatternSpace::hasPoint, edgePointFrom_->get()) &&
           edgePointTo_->isValid() && patterns_->all(&PatternSpace::hasPoint, edgePointTo_->get()) &&
           apexPoint_->isValid() && patterns_->all(&PatternSpace::hasPoint, apexPoint_->get()) &&
           leg1Point_->isValid() && patterns_->all(&PatternSpace::hasPoint, leg1Point_->get()) && intake_->isValid();
}

void UnfoldEdgeDartInstruction::execute() {
    const auto leg1Point = patterns_->onAny(&PatternSpace::getPoint, leg1Point_->get());
    const auto apexPoint = patterns_->onAny(&PatternSpace::getPoint, apexPoint_->get());
    const auto edgePointFrom = patterns_->onAny(&PatternSpace::getPoint, edgePointFrom_->get());
    const auto edgePointTo = patterns_->onAny(&PatternSpace::getPoint, edgePointTo_->get());
    const auto legLength = ProjectSpace::length(*leg1Point, *apexPoint);
    const auto leg2Point = space().addPoint(ProjectSpace::circlesIntersection(
            *edgePointTo,
            *apexPoint, legLength,
            *leg1Point, intake_->get())
    );
    const auto edgeAngle = ProjectSpace::angle(*edgePointFrom, *edgePointTo);
    const auto dartAngle = ProjectSpace::angle(*apexPoint - *leg1Point, *apexPoint - *leg2Point);

    space().movePoint(edgePointTo, ProjectSpace::relativePoint(*leg2Point, edgeAngle + dartAngle, ProjectSpace::length(*leg1Point, *edgePointTo)));
    for (const auto& pattern: *patterns_) {
        pattern->notify(&PatternSpaceObserver::relativePointConnectionRemoved, edgePointFrom, edgePointTo);
        pattern->notify(&PatternSpaceObserver::relativePointConnectionAdded, edgePointFrom, leg1Point);
        pattern->notify(&PatternSpaceObserver::relativePointConnectionAdded, leg2Point, edgePointTo);
        pattern->notify(&PatternSpaceObserver::relativePointConnectionRemoved, edgePointFrom, leg1Point);
        pattern->notify(&PatternSpaceObserver::relativePointConnectionAdded, leg1Point, apexPoint);
        pattern->notify(&PatternSpaceObserver::relativePointConnectionAdded, apexPoint, leg2Point);
        pattern->addPoint(leg1Point_->get() + "_1", leg2Point);
    }
}
