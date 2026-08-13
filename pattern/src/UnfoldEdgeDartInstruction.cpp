#include "instructions/UnfoldEdgeDartInstruction.h"

using namespace Chrysalis;

UnfoldEdgeDartInstruction::UnfoldEdgeDartInstruction(ProjectSpace* space, args::patterns* patterns,
                                                     const args::segment* edge, const args::segment* leg, args::number&& intake)
    : BasePatternInstruction(space, patterns), edge_(edge), leg_(leg), intake_(std::move(intake)) {}

UnfoldEdgeDartInstruction::~UnfoldEdgeDartInstruction() {
    delete edge_;
    delete leg_;
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
            *leg1Point, intake_->get().value())
    );
    const auto edgeAngle = CG::angle(*edgePointFrom, *edgePointTo);
    const auto dartAngle = CG::angle(*apexPoint - *leg1Point, *apexPoint - *leg2Point);

    space().movePoint(edgePointTo, CG::relativePoint(*leg2Point, edgeAngle + dartAngle, CG::length(*leg1Point, *edgePointTo)));
    for (const auto& pattern: *patterns_) {
        pattern->trace::notify(&PatternTraceObserver::relativePointConnectionRemoved, edgePointFrom, edgePointTo);
        pattern->trace::notify(&PatternTraceObserver::relativePointConnectionAdded, edgePointFrom, leg1Point);
        pattern->trace::notify(&PatternTraceObserver::relativePointConnectionAdded, leg2Point, edgePointTo);
        pattern->trace::notify(&PatternTraceObserver::relativePointConnectionRemoved, edgePointFrom, leg1Point);
        pattern->trace::notify(&PatternTraceObserver::relativePointConnectionAdded, leg1Point, apexPoint);
        pattern->trace::notify(&PatternTraceObserver::relativePointConnectionAdded, apexPoint, leg2Point);
        pattern->addPoint(leg_->origin()->name()->get().value() + "_1", leg2Point);
    }
}
