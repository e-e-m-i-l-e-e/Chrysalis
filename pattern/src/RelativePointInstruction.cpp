#include "instructions/RelativePointInstruction.h"

using namespace Chrysalis;

RelativePointInstruction::RelativePointInstruction(ProjectSpace* space, SelectedPatternsArgument* selectedPatterns,
                                                   const name* pointFrom, const pattern* pointFromPattern,
                                                   const name* pointTo, const num* angle, const num* distance)
    : BasePatternInstruction(space, selectedPatterns), pointFrom_(pointFrom),
      pointFromPattern_(pointFromPattern), pointTo_(pointTo), angle_(angle),
      distance_(distance) {}

RelativePointInstruction::~RelativePointInstruction() {
    delete pointFrom_;
    delete pointFromPattern_;
    delete pointTo_;
    delete angle_;
    delete distance_;
}

bool RelativePointInstruction::isValid() {
    if (pointFrom_->hasArgument()) {
        std::unordered_set<const Point*> points;
        for (const auto& patternSpace: patterns()) {
            points.insert(patternSpace->getPoint(pointFrom_->getArgument()));
        }
        if (points.size() != 1) return false;
    } else {
        std::unordered_set<const Point*> points;
        for (const auto& patternSpace: patterns()) {
            const Point* lastPoint = patternSpace->getPoint(pointTo_->getArgument());
            if (!lastPoint) return false;
            points.insert(lastPoint);
        }
        if (points.size() != 1) return false;
    }
    return pointTo_->hasArgument() && angle_->hasArgument() && distance_->hasArgument();
}

void RelativePointInstruction::execute() {
    const Point* pointFrom;
    if (pointFrom_->hasArgument()) {
        if (pointFromPattern_->hasArgument()) {
            const PatternSpace* patternSpaceFrom = pointFromPattern_->getArgument();
            pointFrom = patternSpaceFrom->getPoint(pointFrom_->getArgument());
        } else {
            pointFrom = (*patterns().begin())->getPoint(pointFrom_->getArgument());
        }
    } else {
        pointFrom = (*patterns().begin())->getLastPoint();
    }
    Point* point = space().addPoint(pointFrom, angle_->getArgument(), distance_->getArgument());
    for (const auto& patternSpace: patterns()) {
        patternSpace->addPoint(pointTo_->getArgument(), point);
    }
}
