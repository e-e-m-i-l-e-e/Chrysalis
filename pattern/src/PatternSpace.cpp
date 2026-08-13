#include "PatternSpace.h"

using namespace Chrysalis;

PatternSpace::PatternSpace(OutlineContainer outline): outline_(std::move(outline)) {}

PatternSpace* PatternSpace::create() {
    return new PatternSpace(std::make_unique<NamedElementsContainer<Outline>>());
}

const Point* PatternSpace::getLastPoint() const {
    return lastPoint_;
}

const OutlineContainer& PatternSpace::getOutline() const {
    return outline_;
}

bool PatternSpace::hasPoint(const std::string& name) const {
    return points_.contains(name);
}

bool PatternSpace::hasOutline(const std::string& name) const {
    return outline_->has(name);
}

const Point* PatternSpace::getPoint(const std::string& name) const {
    return points_.at(name);
}

const std::unordered_map<std::string, const Point*>& PatternSpace::getPoints() const {
    return points_;
}

void PatternSpace::addPoint(const std::string& name, const Point* point) {
    points_[name] = point;
    lastPoint_ = point;
    trace::notify(&PatternTraceObserver::pointAdded, point);
}

void PatternSpace::transform(const Transformation& transformation) {
    transformation_ = transformation;
    trace::notify(&PatternTraceObserver::transformed, transformation_);
}

const Transformation& PatternSpace::getTransformation() const {
    return transformation_;
}
