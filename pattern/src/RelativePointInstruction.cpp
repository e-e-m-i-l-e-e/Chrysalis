#include "instructions/RelativePointInstruction.h"

using namespace Chrysalis;

RelativePointInstruction::RelativePointInstruction(ProjectSpace* space, SelectedPatternsArgument* selectedPatterns,
                                                   const point* origin, const name* pointTo, const num* angle, const num* distance)
    : BasePatternInstruction(space, selectedPatterns), origin_(origin), pointTo_(pointTo), angle_(angle),
      distance_(distance) {}

RelativePointInstruction::~RelativePointInstruction() {
    delete origin_;
    delete pointTo_;
    delete angle_;
    delete distance_;
}

bool RelativePointInstruction::isValid() {
    if (!origin_->isValid()) {
        std::unordered_set<const Point*> points;
        for (const auto& patternSpace: patterns()) {
            const Point* lastPoint = patternSpace->getPoint(pointTo_->get());
            if (!lastPoint) return false;
            points.insert(lastPoint);
        }
        if (points.size() != 1) return false;
    }
    return pointTo_->hasValue() && angle_->hasValue() && distance_->hasValue();
}

void RelativePointInstruction::execute() {
    const Point* pointFrom = origin_->isValid() ? origin_->get() : (*patterns().begin())->getLastPoint();
    Point* point = space().addPoint(ProjectSpace::relativePoint(*pointFrom, angle_->get(), distance_->get()));
    for (const auto& patternSpace: patterns()) {
        patternSpace->addPoint(pointTo_->get(), point);
        patternSpace->notify(&PatternSpaceObserver::relativePointConnectionAdded, pointFrom, point);
    }
}