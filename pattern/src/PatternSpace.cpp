#include "PatternSpace.h"

PatternSpace::PatternSpace(Space* space)
    : space_(space) {}

bool PatternSpace::hasPoint(const std::string& name) const {
    return points_.contains(name);
}

Point* PatternSpace::getPoint(const std::string& name) const {
    return points_.at(name);
}

void PatternSpace::addPoint(const std::string& name, Point* point) {
    points_[name] = point;
}
