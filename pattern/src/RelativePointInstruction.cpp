#include "instructions/RelativePointInstruction.h"

using namespace Chrysalis;

RelativePointInstruction::RelativePointInstruction(ProjectSpace* space, args::patterns* selectedPatterns,
                                                   const args::name* name, const args::vector* vector)
    : RelativePointInstruction(space, selectedPatterns, name, vector, new args::optional<args::line>()) {}

RelativePointInstruction::RelativePointInstruction(ProjectSpace* space, args::patterns* selectedPatterns,
                                                   const args::name* name, const args::vector* vector,
                                                   const args::optional<args::line>* line)
    : BasePatternInstruction(space, selectedPatterns), name_(name), vector_(vector), line_(line) {}

RelativePointInstruction::~RelativePointInstruction() {
    delete name_;
    delete vector_;
    delete line_;
}

bool RelativePointInstruction::isValid() {
    if (!dynamic_cast<const PatternPointArgument*>(vector_->origin())) {
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
    Point* point;
    const Point* pointFrom = dynamic_cast<const PatternPointArgument*>(vector_->origin()) ? dynamic_cast<const PatternPointArgument*>(vector_->origin())->get() : patterns_->onAny(&PatternSpace::getLastPoint);
    if (line_->hasArgument()) {
        const auto projection = CG::projection(*pointFrom, static_cast<CG::Line>(*line_->argument()));
        const double distance = sqrt(pow(vector_->length()->get(), 2) + CGAL::squared_distance<CG::LinearKernel>(*pointFrom, projection));
        point = space().addPoint(CG::relativePoint(projection, line_->argument()->angle()->get(), distance));
    } else {
        point = space().addPoint(CG::relativePoint(*pointFrom, vector_->angle()->get(), vector_->length()->get()));
    }
    for (const auto& patternSpace: *patterns_) {
        patternSpace->addPoint(name_->get(), point);
        patternSpace->notify(&PatternSpaceObserver::relativePointConnectionAdded, pointFrom, point);
    }
}