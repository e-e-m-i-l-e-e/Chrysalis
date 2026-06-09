#include "Outline.h"

using namespace Chrysalis;

Outline::Outline(const std::string& name): name_(name) {}

Outline::Outline(const std::string& name, const std::string& firstPoint): name_(name) {
    points_.push_back(firstPoint);
}

const std::string& Outline::getName() {
    return name_;
}

void Outline::addPoint(const std::string& name) {
    points_.push_back(name);
}
