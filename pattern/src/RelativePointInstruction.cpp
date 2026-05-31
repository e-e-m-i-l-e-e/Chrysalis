#include "RelativePointInstruction.h"

using namespace Chrysalis;

RelativePointInstruction::RelativePointInstruction(ProjectSpace* space,
                                                   Argument<PatternSpacesArgument*>* patternSpaces,
                                                   Argument<std::string>* pointFrom,
                                                   Argument<PatternSpace*>* pointFromPatternSpace,
                                                   Argument<std::string>* pointTo,
                                                   Argument<double>* angle,
                                                   Argument<double>* distance)
    : BasePatternSpacesInstruction(space, patternSpaces), pointFrom_(pointFrom),
      pointFromPatternSpace_(pointFromPatternSpace), pointTo_(pointTo), angle_(angle),
      distance_(distance) {
    patternSpaces_->addObserver(this);
    pointFrom_->addObserver(this);
    pointFromPatternSpace_->addObserver(this);
    pointTo_->addObserver(this);
    angle_->addObserver(this);
    distance_->addObserver(this);
}

RelativePointInstruction::~RelativePointInstruction() {
    delete pointFrom_;
    delete pointFromPatternSpace_;
    delete pointTo_;
    delete angle_;
    delete distance_;
}

void RelativePointInstruction::reset() {
}

bool RelativePointInstruction::isValid() {
    if (pointFrom_->hasArgument()) {
        std::unordered_set<Point*> points;
        for (const auto& patternSpace: *patternSpaces_->getArgument()) {
            points.insert(patternSpace->getPoint(pointFrom_->getArgument()));
        }
        if (points.size() != 1) return false;
    } else {
        std::unordered_set<Point*> points;
        for (const auto& patternSpace: *patternSpaces_->getArgument()) {
            Point* lastPoint = patternSpace->getPoint(pointTo_->getArgument());
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
        if (pointFromPatternSpace_->hasArgument()) {
            const PatternSpace* patternSpaceFrom = pointFromPatternSpace_->getArgument();
            pointFrom = patternSpaceFrom->getPoint(pointFrom_->getArgument());
        } else {
            pointFrom = (*patternSpaces_->getArgument()->begin())->getPoint(pointFrom_->getArgument());
        }
    } else {
        pointFrom = (*patternSpaces_->getArgument()->begin())->getLastPoint();
    }
    Point* point = space_->addPoint(pointFrom, angle_->getArgument(), distance_->getArgument());
    for (const auto& patternSpace: *patternSpaces_->getArgument()) {
        patternSpace->addPoint(pointTo_->getArgument(), point);
    }
}
