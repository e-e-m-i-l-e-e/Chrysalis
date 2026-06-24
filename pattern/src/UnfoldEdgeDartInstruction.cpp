#include "instructions/UnfoldEdgeDartInstruction.h"

using namespace Chrysalis;

UnfoldEdgeDartInstruction::UnfoldEdgeDartInstruction(ProjectSpace* space, SelectedPatternsArgument* patterns,
                                                     const name* edgePointFrom, const name* edgePointTo,
                                                     const name* apexPoint, const name* leg1Point, const num* intake)
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
    return edgePointFrom_->hasArgument() && eachPatternHasPoint(edgePointFrom_->getArgument()) &&
           edgePointTo_->hasArgument() && eachPatternHasPoint(edgePointTo_->getArgument()) &&
           apexPoint_->hasArgument() && eachPatternHasPoint(apexPoint_->getArgument()) &&
           leg1Point_->hasArgument() && eachPatternHasPoint(leg1Point_->getArgument()) && intake_->hasArgument();
}

void UnfoldEdgeDartInstruction::execute() {
    const auto leg1Point = anyPattern()->getPoint(leg1Point_->getArgument());
    const auto apexPoint = anyPattern()->getPoint(apexPoint_->getArgument());
    const auto edgePointFrom = anyPattern()->getPoint(edgePointFrom_->getArgument());
    const auto edgePointTo = anyPattern()->getPoint(edgePointTo_->getArgument());
    const auto legLength = ProjectSpace::length(*leg1Point, *apexPoint);
    const auto leg2Point = space().addPoint(ProjectSpace::circlesIntersection(
            *edgePointTo,
            *apexPoint, legLength,
            *leg1Point, intake_->getArgument())
    );
    const auto edgeAngle = ProjectSpace::angle(*edgePointFrom, *edgePointTo);
    const auto dartAngle = ProjectSpace::angle(*apexPoint - *leg1Point, *apexPoint - *leg2Point);

    space().movePoint(edgePointTo, ProjectSpace::relativePoint(*leg2Point, edgeAngle + dartAngle, ProjectSpace::length(*leg1Point, *edgePointTo)));
    for (const auto& pattern: patterns()) {
        pattern->notify(&PatternSpaceObserver::relativePointConnectionRemoved, edgePointFrom, edgePointTo);
        pattern->notify(&PatternSpaceObserver::relativePointConnectionAdded, edgePointFrom, leg1Point);
        pattern->notify(&PatternSpaceObserver::relativePointConnectionAdded, leg2Point, edgePointTo);
        pattern->notify(&PatternSpaceObserver::relativePointConnectionRemoved, edgePointFrom, leg1Point);
        pattern->notify(&PatternSpaceObserver::relativePointConnectionAdded, leg1Point, apexPoint);
        pattern->notify(&PatternSpaceObserver::relativePointConnectionAdded, apexPoint, leg2Point);
        pattern->addPoint(leg1Point_->getArgument() + "_1", leg2Point);
    }
}
