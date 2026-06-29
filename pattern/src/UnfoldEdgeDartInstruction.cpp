#include "instructions/UnfoldEdgeDartInstruction.h"

using namespace Chrysalis;

UnfoldEdgeDartInstruction::UnfoldEdgeDartInstruction(ProjectSpace* space, args::patterns* patterns,
                                                     const args::segment* edge, const args::segment* leg, const args::number* intake)
    : BasePatternInstruction(space, patterns), edge_(edge), leg_(leg), intake_(intake) {}

UnfoldEdgeDartInstruction::~UnfoldEdgeDartInstruction() {
    delete edge_;
    delete leg_;
    delete intake_;
}

bool UnfoldEdgeDartInstruction::isValid() {
    return edge_->isValid() && leg_->isValid() && intake_->isValid();
}

void UnfoldEdgeDartInstruction::execute() {
    const auto leg1Point = leg_->origin()->get();
    const auto apexPoint = leg_->destination()->get();
    const auto edgePointFrom = edge_->origin()->get();
    const auto edgePointTo = edge_->destination()->get();
    const auto legLength = CG::length(*leg1Point, *apexPoint);
    const auto leg2Point = space().addPoint(CG::circlesIntersection(
            *edgePointTo,
            *apexPoint, legLength,
            *leg1Point, intake_->get())
    );
    const auto edgeAngle = CG::angle(*edgePointFrom, *edgePointTo);
    const auto dartAngle = CG::angle(*apexPoint - *leg1Point, *apexPoint - *leg2Point);

    space().movePoint(edgePointTo, CG::relativePoint(*leg2Point, edgeAngle + dartAngle, CG::length(*leg1Point, *edgePointTo)));
    for (const auto& pattern: *patterns_) {
        pattern->notify(&PatternSpaceObserver::relativePointConnectionRemoved, edgePointFrom, edgePointTo);
        pattern->notify(&PatternSpaceObserver::relativePointConnectionAdded, edgePointFrom, leg1Point);
        pattern->notify(&PatternSpaceObserver::relativePointConnectionAdded, leg2Point, edgePointTo);
        pattern->notify(&PatternSpaceObserver::relativePointConnectionRemoved, edgePointFrom, leg1Point);
        pattern->notify(&PatternSpaceObserver::relativePointConnectionAdded, leg1Point, apexPoint);
        pattern->notify(&PatternSpaceObserver::relativePointConnectionAdded, apexPoint, leg2Point);
        pattern->addPoint(leg_->origin()->name()->get() + "_1", leg2Point);
    }
}
