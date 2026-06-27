#include "instructions/RelativePointInstruction.h"

using namespace Chrysalis;

RelativePointInstruction::RelativePointInstruction(ProjectSpace* space, SelectedPatternsArgument* selectedPatterns,
                                                   const OptionalArgument<point>* origin, const name* pointTo, const num* angle, const num* distance)
    : BasePatternInstruction(space, selectedPatterns), origin_(origin), pointTo_(pointTo), angle_(angle),
      distance_(distance) {}

RelativePointInstruction::~RelativePointInstruction() {
    delete origin_;
    delete pointTo_;
    delete angle_;
    delete distance_;
}

bool RelativePointInstruction::isValid() {
    if (!origin_->argument()) {
        std::unordered_set<const Point*> points;
        for (const auto& patternSpace: patterns()) {
            const Point* lastPoint = patternSpace->getPoint(pointTo_->get());
            if (!lastPoint) return false;
            points.insert(lastPoint);
        }
        if (points.size() != 1) return false;
    }
    return pointTo_->isValid() && angle_->isValid() && distance_->isValid();
}

void RelativePointInstruction::execute() {
    const Point* pointFrom = origin_->hasArgument() ? origin_->argument()->get() : (*patterns().begin())->getLastPoint();
    Point* point = space().addPoint(ProjectSpace::relativePoint(*pointFrom, angle_->get(), distance_->get()));
    for (const auto& patternSpace: patterns()) {
        patternSpace->addPoint(pointTo_->get(), point);
        patternSpace->notify(&PatternSpaceObserver::relativePointConnectionAdded, pointFrom, point);
    }
}