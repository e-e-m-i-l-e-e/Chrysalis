#include "instructions/DartInstruction.h"

Chrysalis::DartInstruction::DartInstruction(ProjectSpace* space, SelectedPatternsArgument* patterns, const name* point,
                                            const num* angle, const num* length, const num* edgeAngle,
                                            const num* leg1Length, const num* leg2Length, const SelectedNamesArgument* selectedPoints)
    : BasePatternInstruction(space, patterns), angle_(angle), length_(length), point_(point), edgeAngle_(edgeAngle),
      leg1Length_(leg1Length), leg2Length_(leg2Length), selectedPoints_(selectedPoints) {}

Chrysalis::DartInstruction::~DartInstruction() {
    delete point_;
    delete angle_;
    delete length_;
    delete edgeAngle_;
    delete leg1Length_;
    delete leg2Length_;
    delete selectedPoints_;
}

bool Chrysalis::DartInstruction::isValid() {
    for (const auto& selectedPoint: *selectedPoints_) {
        if (!eachPatternHasPoint(selectedPoint)) return false;
    }
    return point_->hasArgument() && eachPatternHasPoint(point_->getArgument()) &&
           angle_->hasArgument() && length_->hasArgument() && leg1Length_->hasArgument();
}

void Chrysalis::DartInstruction::execute() {
    std::cout << "Angle " << angle_->getArgument() << " edgeAngle: " << edgeAngle_->getArgument() << " length: " << length_->getArgument() << " leg1: " << leg1Length_->getArgument() << std::endl;
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
    const double dartAngle = ProjectSpace::angle(*leg1Point - *centerPoint, *leg2Point - *centerPoint);
    for (const auto& selectedPointName: *selectedPoints_) {
        const Point* selectedPoint = (*patterns().begin())->getPoint(selectedPointName);

        const auto rotatedOffset = ProjectSpace::rotate(*selectedPoint - *leg2Point, -dartAngle);
        Point* newPoint = space().addPoint(
            leg2Point->x() + rotatedOffset.x(),
            leg2Point->y() + rotatedOffset.y());

        const std::string newPointName = selectedPointName + "'"; // or whatever naming convention fits
        for (const auto& pattern: patterns()) {
            pattern->addPoint(newPointName, newPoint);
            pattern->notify(&PatternSpaceObserver::pointAdded, newPoint);
        }
        std::cout << "New point: " << newPoint->x() << " " << newPoint->y() << std::endl;
        std::cout << "Angle = " << ProjectSpace::angle(*leg1Point - *selectedPoint, *leg1Point - *newPoint) << std::endl;
    }
}
