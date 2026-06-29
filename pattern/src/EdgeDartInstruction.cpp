#include "instructions/EdgeDartInstruction.h"

using namespace Chrysalis;

EdgeDartInstruction::EdgeDartInstruction(ProjectSpace* space, args::patterns* patterns,
                                         const args::segment* edge, const args::vector* dart,
                                         const args::number* leg1Intake, const args::optional<args::number>* leg2Intake)
    : BasePatternInstruction(space, patterns), edge_(edge), dart_(dart), leg1Intake_(leg1Intake), leg2Intake_(leg2Intake) {}

EdgeDartInstruction::~EdgeDartInstruction() {
    delete edge_;
    delete dart_;
    delete leg1Intake_;
    delete leg2Intake_;
}

bool EdgeDartInstruction::isValid() {
    return edge_->isValid() && dart_->isValid() && leg1Intake_->isValid();
}

void EdgeDartInstruction::execute() {
    const Point* point = dart_->origin()->get();
    double leg1Intake, leg2Intake;
    if (leg2Intake_->argument()) {
        leg1Intake = leg1Intake_->get();
        leg2Intake = leg2Intake_->argument()->get();
    } else {
        leg1Intake = leg2Intake = leg1Intake_->get() / 2;
    }

    const double edgeAngle = ProjectSpace::angle(*edge_->origin()->get(), *edge_->destination()->get());

    const double angle = dart_->angle()->get();
    const Point* centerPoint = space().addPoint(ProjectSpace::relativePoint(*point, edgeAngle - angle, dart_->getLength()));
    const Point* leg1Point = space().addPoint(ProjectSpace::relativePoint(*point, edgeAngle + 180, leg1Intake));
    const Point* leg2Point = space().addPoint(ProjectSpace::relativePoint(*point, edgeAngle, leg2Intake));

    const std::string centerPointName = dart_->origin()->name()->get() + "A";
    const std::string leg1PointName = dart_->origin()->name()->get() + "1";
    const std::string leg2PointName = dart_->origin()->name()->get() + "2";

    for (const auto& pattern: *patterns_) {
        pattern->addPoint(centerPointName, centerPoint);
        pattern->addPoint(leg1PointName, leg1Point);
        pattern->addPoint(leg2PointName, leg2Point);

        pattern->notify(&PatternSpaceObserver::relativePointConnectionRemoved, edge_->origin()->get(), edge_->destination()->get());
        pattern->notify(&PatternSpaceObserver::relativePointConnectionAdded, edge_->origin()->get(), leg1Point);
        pattern->notify(&PatternSpaceObserver::relativePointConnectionAdded, leg1Point, centerPoint);
        pattern->notify(&PatternSpaceObserver::relativePointConnectionAdded, centerPoint, leg2Point);
        pattern->notify(&PatternSpaceObserver::relativePointConnectionAdded, leg2Point, edge_->destination()->get());
    }
    const double dartAngle = ProjectSpace::angle(*leg1Point - *centerPoint, *leg2Point - *centerPoint);
    const auto adjustedVector = ProjectSpace::rotate(*edge_->destination()->get() - *leg2Point, -dartAngle);
    space().movePoint(edge_->destination()->get(), *leg2Point + adjustedVector);
}
