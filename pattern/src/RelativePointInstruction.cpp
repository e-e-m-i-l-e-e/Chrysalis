#include "instructions/RelativePointInstruction.h"

using namespace Chrysalis;

RelativePointInstruction::RelativePointInstruction(ProjectSpace* space, args::patterns* selectedPatterns,
                                                   const args::optional<args::point>* origin, const args::name* name,
                                                   const args::vector* vector)
    : BasePatternInstruction(space, selectedPatterns), origin_(origin), name_(name), vector_(vector) {}

RelativePointInstruction::~RelativePointInstruction() {
    delete origin_;
    delete name_;
    delete vector_;
}

bool RelativePointInstruction::isValid() {
    if (!origin_->argument()) {
        std::unordered_set<const Point*> points;
        for (const auto& patternSpace: *patterns_) {
            const Point* lastPoint = patternSpace->getPoint(name_->get());
            if (!lastPoint) return false;
            points.insert(lastPoint);
        }
        if (points.size() != 1) return false;
    }
    return vector_->isValid();
}

void RelativePointInstruction::execute() {
    const Point* pointFrom = origin_->hasArgument() ? origin_->argument()->get() : patterns_->onAny(&PatternSpace::getLastPoint);
    Point* point = space().addPoint(CG::relativePoint(*pointFrom, vector_->angle()->get(), vector_->length()->get()));
    for (const auto& patternSpace: *patterns_) {
        patternSpace->addPoint(name_->get(), point);
        patternSpace->notify(&PatternSpaceObserver::relativePointConnectionAdded, pointFrom, point);
    }
}