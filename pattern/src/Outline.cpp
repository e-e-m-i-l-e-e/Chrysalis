#include "Outline.h"

using namespace Chrysalis;

Outline::Outline(const std::string& name): name_(name) {}

Outline::Outline(const std::string& name, const std::string& firstPoint): name_(name) {
    points_.push_back(firstPoint);
}

const std::string& Outline::getName() const{
    return name_;
}

const std::list<std::string>& Outline::getPoints() const {
    return points_;
}

void Outline::addPoint(const std::string& name) {
    points_.push_back(name);
}
