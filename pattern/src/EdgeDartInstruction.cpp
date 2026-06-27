#include "instructions/EdgeDartInstruction.h"

using namespace Chrysalis;

EdgeDartInstruction::EdgeDartInstruction(ProjectSpace* space, args::patterns* patterns,
                                         const args::name* edgePointFrom, const args::name* edgePointTo, const vector* dartVector,
                                         const args::number* leg1Intake, const OptionalArgument<args::number>* leg2Intake)
    : BasePatternInstruction(space, patterns), edgePointFrom_(edgePointFrom), edgePointTo_(edgePointTo),
      dartVector_(dartVector), leg1Intake_(leg1Intake), leg2Intake_(leg2Intake) {}

EdgeDartInstruction::~EdgeDartInstruction() {
    delete edgePointFrom_;
    delete edgePointTo_;
    delete dartVector_;
    delete leg1Intake_;
    delete leg2Intake_;
}

bool EdgeDartInstruction::isValid() {
    return
        edgePointFrom_->isValid() && patterns_->all(&PatternSpace::hasPoint, edgePointFrom_->get()) &&
        edgePointTo_->isValid() && patterns_->all(&PatternSpace::hasPoint, edgePointTo_->get()) &&
        dartVector_->isValid() && leg1Intake_->isValid();
}

void EdgeDartInstruction::execute() {
    const Point* point = dartVector_->getOrigin();
    double leg1Intake, leg2Intake;
    if (leg2Intake_->argument()) {
        leg1Intake = leg1Intake_->get();
        leg2Intake = leg2Intake_->argument()->get();
    } else {
        leg1Intake = leg2Intake = leg1Intake_->get() / 2;
    }

    const Point* edgePointFrom = patterns_->onAny(&PatternSpace::getPoint, edgePointFrom_->get());
    auto edgePointTo = patterns_->onAny(&PatternSpace::getPoint, edgePointTo_->get());
    const double edgeAngle = ProjectSpace::angle(*edgePointFrom, *edgePointTo);

    const double angle = dartVector_->getAngle();
    const Point* centerPoint = space().addPoint(ProjectSpace::relativePoint(*point, edgeAngle - angle, dartVector_->getLength()));
    const Point* leg1Point = space().addPoint(ProjectSpace::relativePoint(*point, edgeAngle + 180, leg1Intake));
    const Point* leg2Point = space().addPoint(ProjectSpace::relativePoint(*point, edgeAngle, leg2Intake));

    const std::string centerPointName = dartVector_->getOriginName() + "A";
    const std::string leg1PointName = dartVector_->getOriginName() + "1";
    const std::string leg2PointName = dartVector_->getOriginName() + "2";

    for (const auto& pattern: *patterns_) {
        pattern->addPoint(centerPointName, centerPoint);
        pattern->addPoint(leg1PointName, leg1Point);
        pattern->addPoint(leg2PointName, leg2Point);

        pattern->notify(&PatternSpaceObserver::relativePointConnectionRemoved, edgePointFrom, edgePointTo);
        pattern->notify(&PatternSpaceObserver::relativePointConnectionAdded, edgePointFrom, leg1Point);
        pattern->notify(&PatternSpaceObserver::relativePointConnectionAdded, leg1Point, centerPoint);
        pattern->notify(&PatternSpaceObserver::relativePointConnectionAdded, centerPoint, leg2Point);
        pattern->notify(&PatternSpaceObserver::relativePointConnectionAdded, leg2Point, edgePointTo);
    }
    const double dartAngle = ProjectSpace::angle(*leg1Point - *centerPoint, *leg2Point - *centerPoint);
    const auto adjustedVector = ProjectSpace::rotate(*edgePointTo - *leg2Point, -dartAngle);
    space().movePoint(edgePointTo, *leg2Point + adjustedVector);
}
