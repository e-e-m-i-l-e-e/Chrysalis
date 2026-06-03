#include "PatternSpace.h"

using namespace Chrysalis;

PatternSpace::PatternSpace(OutlineContainer* outline): outline_(outline) {}

PatternSpace::~PatternSpace() {
    delete outline_;
}

Point* PatternSpace::getLastPoint() const {
    return lastPoint_;
}

OutlineContainer* PatternSpace::getOutline() const {
    return outline_;
}

bool PatternSpace::hasPoint(const std::string& name) const {
    return points_.contains(name);
}

Point* PatternSpace::getPoint(const std::string& name) const {
    return points_.at(name);
}

const std::unordered_map<std::string, Point*>& PatternSpace::getPoints() const {
    return points_;
}

void PatternSpace::addPoint(const std::string& name, Point* point) {
    points_[name] = point;
    lastPoint_ = point;
}
