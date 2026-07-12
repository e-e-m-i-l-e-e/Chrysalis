#include "Outline.h"

using namespace Chrysalis;

Outline::Outline(const std::string& name): BaseNamedElement(name) {}

const std::vector<const Point*>& Outline::points() const {
    return points_;
}

void Outline::add(const Point* point) {
    points_.push_back(point);
}
