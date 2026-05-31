#include "PatternSpace.h"

using namespace Chrysalis;

Point* PatternSpace::getLastPoint() const {
    return lastPoint_;
}

bool PatternSpace::hasPoint(const std::string& name) const {
    return points_.contains(name);
}

Point* PatternSpace::getPoint(const std::string& name) const {
    return points_.at(name);
}

void PatternSpace::addPoint(const std::string& name, Point* point) {
    points_[name] = point;
    lastPoint_ = point;
}
