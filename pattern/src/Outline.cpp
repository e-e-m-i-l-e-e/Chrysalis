#include "Outline.h"

Chrysalis::Outline::Outline(const std::string& name, const std::string& firstPoint): name_(name) {
    points_.push_back(firstPoint);
}

const std::string& Chrysalis::Outline::getName() {
    return name_;
}

void Chrysalis::Outline::addPoint(const std::string& name) {
    points_.push_back(name);
}
