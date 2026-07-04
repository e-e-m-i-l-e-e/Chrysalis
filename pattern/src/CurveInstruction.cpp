#include "instructions/CurveInstruction.h"

#include <vector>

using namespace Chrysalis;

CurveInstruction::CurveInstruction(ProjectSpace* space, args::patterns* patterns, const args::vector* from,
                                   const args::vector* to,
                                   const args::container<PatternPointArgument>* points) :
    BasePatternInstruction(space, patterns), from_(from), to_(to), points_(points) {}

CurveInstruction::~CurveInstruction() {
    delete from_;
    delete to_;
    delete points_;
}

bool CurveInstruction::isValid() {
    return from_->isValid() && to_->isValid();
}

void CurveInstruction::execute() {
    const auto segmentFrom = static_cast<CG::Segment>(*from_);
    const auto segmentTo = static_cast<CG::Segment>(*to_);

    std::vector<CG::Point> points;
    points.reserve(points_->count() + 2);
    points.push_back(segmentFrom.end());
    for (const auto& point : *points_) {
        points.push_back(*point->get());
    }
    points.push_back(segmentTo.end());
    const auto curve = space().addCurve(from_->origin()->get(), to_->origin()->get(), segmentFrom, segmentTo, points);
    for (const auto& pattern: *patterns_) {
        pattern->notify(&PatternSpaceObserver::curveAdded, curve);
    }
}
