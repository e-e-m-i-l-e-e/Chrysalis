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

const std::unordered_map<std::string, Point*>& PatternSpace::getPoints() const {
    return points_;
}

void PatternSpace::addPoint(const std::string& name, Point* point) {
    points_[name] = point;
    lastPoint_ = point;
}
