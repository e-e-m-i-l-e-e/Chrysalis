#include "Outline.h"

using namespace Chrysalis;

Outline::Outline(const std::string& name): BaseNamedElement(name) {}

const std::vector<std::string>& Outline::points() const {
    return points_;
}

void Outline::add(const std::string& name) {
    points_.push_back(name);
}
