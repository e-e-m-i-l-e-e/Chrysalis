#include "instructions/DartInstruction.h"

Chrysalis::DartInstruction::DartInstruction(ProjectSpace* space, args::patterns* patterns,
                                            const PatternPointArgument* point, const args::number* intake,
                                            const args::vector* top, const args::vector* bottom)
    : BasePatternInstruction(space, patterns), point_(point), intake_(intake), top_(top), bottom_(bottom) {}

Chrysalis::DartInstruction::~DartInstruction() {
    delete point_;
    delete intake_;
    delete top_;
    delete bottom_;
}

bool Chrysalis::DartInstruction::isValid() {
    return point_->isValid() && intake_->isValid() && bottom_->isValid();
}

void Chrysalis::DartInstruction::execute() {
    const auto top = space().addPoint(CG::relativePoint(*point_->get(), top_->angle()->get(), top_->length()->get()));
    const auto bottom = space().addPoint(CG::relativePoint(*point_->get(), bottom_->angle()->get(), bottom_->length()->get()));
    const auto leg1 = space().addPoint(CG::relativePoint(*point_->get(), 0, intake_->get() / 2));
    const auto leg2 = space().addPoint(CG::relativePoint(*point_->get(), 180, intake_->get() / 2));
    for (const auto& pattern: *patterns_) {
        pattern->addPoint(point_->name()->get() + "T", top);
        pattern->addPoint(point_->name()->get() + "A", bottom);
        pattern->addPoint(point_->name()->get() + "1", leg1);
        pattern->addPoint(point_->name()->get() + "2", leg2);
        pattern->notify(&PatternSpaceObserver::relativePointConnectionAdded, point_->get(), top);
        pattern->notify(&PatternSpaceObserver::relativePointConnectionAdded, point_->get(), bottom);
        pattern->notify(&PatternSpaceObserver::relativePointConnectionAdded, point_->get(), leg1);
        pattern->notify(&PatternSpaceObserver::relativePointConnectionAdded, point_->get(), leg2);
    }
}
