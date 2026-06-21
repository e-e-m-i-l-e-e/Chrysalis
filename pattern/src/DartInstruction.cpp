#include "instructions/DartInstruction.h"

Chrysalis::DartInstruction::DartInstruction(ProjectSpace* space, SelectedPatternsArgument* patterns, const name* point,
                                            const num* angle, const num* length, const num* edgeAngle,
                                            const num* leg1Length, const num* leg2Length)
    : BasePatternInstruction(space, patterns), angle_(angle), length_(length), point_(point), edgeAngle_(edgeAngle),
      leg1Length_(leg1Length), leg2Length_(leg2Length) {}

Chrysalis::DartInstruction::~DartInstruction() {
    delete point_;
    delete angle_;
    delete length_;
    delete edgeAngle_;
    delete leg1Length_;
    delete leg2Length_;
}

bool Chrysalis::DartInstruction::isValid() {
    return point_->hasArgument() && eachPatternHasPoint(point_) &&
           angle_->hasArgument() && length_->hasArgument() && leg1Length_->hasArgument();
}

void Chrysalis::DartInstruction::execute() {
    const Point* point = (*patterns().begin())->getPoint(point_->getArgument());
    double leg1, leg2;
    if (leg2Length_->hasArgument()) {
        leg1 = leg1Length_->getArgument();
        leg2 = leg2Length_->getArgument();
    } else {
        leg1 = leg2 = leg1Length_->getArgument() / 2;
    }
    double edgeAngle = 0;
    if (edgeAngle_->hasArgument()) edgeAngle = edgeAngle_->getArgument();
    const Point* centerPoint = space().addPoint(*point, angle_->getArgument() + edgeAngle, length_->getArgument());
    const Point* leg1Point = space().addPoint(*point, edgeAngle, leg1);
    const Point* leg2Point = space().addPoint(*point, edgeAngle + 180, leg2);
    const std::string centerPointName = point_->getArgument() + "A";
    const std::string leg1PointName = point_->getArgument() + "1";
    const std::string leg2PointName = point_->getArgument() + "2";
    for (const auto& pattern: patterns()) {
        pattern->addPoint(centerPointName, centerPoint);
        pattern->notify(&PatternSpaceObserver::pointAdded, centerPoint);
        pattern->addPoint(leg1PointName, leg1Point);
        pattern->notify(&PatternSpaceObserver::pointAdded, leg1Point);
        pattern->addPoint(leg2PointName, leg2Point);
        pattern->notify(&PatternSpaceObserver::pointAdded, leg2Point);
    }
}
