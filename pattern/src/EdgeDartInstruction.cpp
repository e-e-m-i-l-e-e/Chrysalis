#include "instructions/EdgeDartInstruction.h"

using namespace Chrysalis;

EdgeDartInstruction::EdgeDartInstruction(ProjectSpace* space, SelectedPatternsArgument* patterns,
                                         const name* edgePointFrom, const name* edgePointTo, const name* dartPoint,
                                         const num* angle, const num* length, const num* leg1Intake, const num* leg2Intake)
    : BasePatternInstruction(space, patterns), edgePointFrom_(edgePointFrom), edgePointTo_(edgePointTo),
      dartPoint_(dartPoint), angle_(angle), length_(length), leg1Intake_(leg1Intake), leg2Intake_(leg2Intake) {}

EdgeDartInstruction::~EdgeDartInstruction() {
    delete edgePointFrom_;
    delete edgePointTo_;
    delete dartPoint_;
    delete angle_;
    delete length_;
    delete leg1Intake_;
    delete leg2Intake_;
}

bool EdgeDartInstruction::isValid() {
    return
        edgePointFrom_->hasArgument() && eachPatternHasPoint(edgePointFrom_->getArgument()) &&
        edgePointTo_->hasArgument() && eachPatternHasPoint(edgePointTo_->getArgument()) &&
        dartPoint_->hasArgument() && eachPatternHasPoint(dartPoint_->getArgument()) &&
        length_->hasArgument() && leg1Intake_->hasArgument();
}

void EdgeDartInstruction::execute() {
    const Point* point = anyPattern()->getPoint(dartPoint_->getArgument());
    double leg1Intake, leg2Intake;
    if (leg2Intake_->hasArgument()) {
        leg1Intake = leg1Intake_->getArgument();
        leg2Intake = leg2Intake_->getArgument();
    } else {
        leg1Intake = leg2Intake = leg1Intake_->getArgument() / 2;
    }

    const Point* edgePointFrom = anyPattern()->getPoint(edgePointFrom_->getArgument());
    const Point* edgePointTo = anyPattern()->getPoint(edgePointTo_->getArgument());
    const double edgeAngle = ProjectSpace::angle(*edgePointFrom, *edgePointTo);

    const double angle = angle_->hasArgument() ? angle_->getArgument() : 90;
    const Point* centerPoint = space().addPoint(*point, angle + edgeAngle, length_->getArgument());
    const Point* leg1Point = space().addPoint(*point, edgeAngle, leg1Intake);
    const Point* leg2Point = space().addPoint(*point, edgeAngle + 180, leg2Intake);

    const std::string centerPointName = dartPoint_->getArgument() + "A";
    const std::string leg1PointName = dartPoint_->getArgument() + "1";
    const std::string leg2PointName = dartPoint_->getArgument() + "2";

    for (const auto& pattern: patterns()) {
        pattern->addPoint(centerPointName, centerPoint);
        pattern->addPoint(leg1PointName, leg1Point);
        pattern->addPoint(leg2PointName, leg2Point);
    }
    const double dartAngle = ProjectSpace::angle(*leg1Point - *centerPoint, *leg2Point - *centerPoint);
    const auto adjustedVector = ProjectSpace::rotate(*edgePointTo - *leg2Point, -dartAngle);
    const_cast<Point*>(edgePointTo)->move(leg2Point->x() + adjustedVector.x(), leg2Point->y() + adjustedVector.y());
    // for (const auto& pattern: patterns()) {
    //     pattern->notify(&PatternSpaceObserver::pointMoved, edgePointTo);
    // }
}
