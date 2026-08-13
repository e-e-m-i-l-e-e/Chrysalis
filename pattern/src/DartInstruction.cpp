#include "instructions/DartInstruction.h"

Chrysalis::DartInstruction::DartInstruction(ProjectSpace* space, args::patterns* patterns,
                                            const PatternPointArgument* point, args::number&& intake,
                                            const args::vector* top, const args::vector* bottom)
    : BasePatternInstruction(space, patterns), point_(point), intake_(std::move(intake)), top_(top), bottom_(bottom) {}

Chrysalis::DartInstruction::~DartInstruction() {
    delete point_;
    delete top_;
    delete bottom_;
}

void Chrysalis::DartInstruction::execute() {
    if (const auto intake = intake_->get();
        const auto name = point_->name()->get())
    {
        const auto top = space().addPoint(CG::relativePoint(*point_->get(), static_cast<CG::Vector>(*top_)));
        const auto bottom = space().addPoint(CG::relativePoint(*point_->get(), static_cast<CG::Vector>(*bottom_)));
        const auto leg1 = space().addPoint(CG::relativePoint(*point_->get(), 0, intake.value() / 2));
        const auto leg2 = space().addPoint(CG::relativePoint(*point_->get(), 180, intake.value() / 2));
        for (const auto& pattern: *patterns_) {
            pattern->addPoint(name.value() + "T", top);
            pattern->addPoint(name.value() + "A", bottom);
            pattern->addPoint(name.value() + "1", leg1);
            pattern->addPoint(name.value() + "2", leg2);
            pattern->trace::notify(&PatternTraceObserver::relativePointConnectionAdded, point_->get(), top);
            pattern->trace::notify(&PatternTraceObserver::relativePointConnectionAdded, point_->get(), bottom);
            pattern->trace::notify(&PatternTraceObserver::relativePointConnectionAdded, point_->get(), leg1);
            pattern->trace::notify(&PatternTraceObserver::relativePointConnectionAdded, point_->get(), leg2);
        }
    }
}
