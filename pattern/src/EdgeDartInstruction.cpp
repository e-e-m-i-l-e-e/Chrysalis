#include "instructions/EdgeDartInstruction.h"

using namespace Chrysalis;

EdgeDartInstruction::EdgeDartInstruction(ProjectSpace* space, args::patterns* patterns,
                                         const args::segment* edge, const args::vector* dart,
                                         args::number&& leg1Intake, const args::optional<args::number>* leg2Intake)
    : BasePatternInstruction(space, patterns), edge_(edge), dart_(dart), leg1Intake_(std::move(leg1Intake)), leg2Intake_(leg2Intake) {}

EdgeDartInstruction::~EdgeDartInstruction() {
    delete edge_;
    delete dart_;
    delete leg2Intake_;
}

void EdgeDartInstruction::execute() {
    const Point* point = dart_->origin()->get();
    double leg1Intake, leg2Intake;
    if (leg2Intake_->argument()) {
        leg1Intake = leg1Intake_->get().value();
        leg2Intake = leg2Intake_->argument()->get()->get().value();
    } else {
        leg1Intake = leg2Intake = leg1Intake_->get().value() / 2;
    }

    const double edgeAngle = CG::angle(*edge_->origin()->get(), *edge_->destination()->get());

    const double angle = dart_->angle()->get().value();
    const Point* centerPoint = space().addPoint(CG::relativePoint(*point, edgeAngle - angle, dart_->length()->get().value()));
    const Point* leg1Point = space().addPoint(CG::relativePoint(*point, edgeAngle + 180, leg1Intake));
    const Point* leg2Point = space().addPoint(CG::relativePoint(*point, edgeAngle, leg2Intake));

    const std::string centerPointName = dart_->origin()->name()->get().value() + "A";
    const std::string leg1PointName = dart_->origin()->name()->get().value() + "1";
    const std::string leg2PointName = dart_->origin()->name()->get().value() + "2";

    for (const auto& pattern: *patterns_) {
        pattern->addPoint(centerPointName, centerPoint);
        pattern->addPoint(leg1PointName, leg1Point);
        pattern->addPoint(leg2PointName, leg2Point);

        pattern->trace::notify(&PatternTraceObserver::relativePointConnectionRemoved, edge_->origin()->get(), edge_->destination()->get());
        pattern->trace::notify(&PatternTraceObserver::relativePointConnectionAdded, edge_->origin()->get(), leg1Point);
        pattern->trace::notify(&PatternTraceObserver::relativePointConnectionAdded, leg1Point, centerPoint);
        pattern->trace::notify(&PatternTraceObserver::relativePointConnectionAdded, centerPoint, leg2Point);
        pattern->trace::notify(&PatternTraceObserver::relativePointConnectionAdded, leg2Point, edge_->destination()->get());
    }
    const double dartAngle = CG::angle(*leg1Point - *centerPoint, *leg2Point - *centerPoint);
    const auto adjustedVector = CG::rotate(*edge_->destination()->get() - *leg2Point, -dartAngle);
    space().movePoint(edge_->destination()->get(), *leg2Point + adjustedVector);
}
