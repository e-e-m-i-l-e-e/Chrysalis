#include "Pattern.h"

using namespace PB;

Pattern::Pattern(const std::string& name, Space* space, Outline* outline)
    : name_(name), space_(space), outline_(outline) {}

void Pattern::addPoint(const std::string& name, const double x, const double y) const {
    space_->addPoint(name, x, y);
}

void Pattern::addPoint(const std::string& from, const std::string& to, const BaseArgument* angle, const BaseArgument* length) const {
    space_->addPoint(from, to, angle->getValue() * CGAL_PI / 180.0, length->getValue());
}

void Pattern::addPoint(const std::string& from, const std::string& to, const Space::Direction direction, const BaseArgument* length) const {
    space_->addPoint(from, to, direction, length->getValue());
}

void Pattern::nextPoint(const std::string& to, Space::Direction direction, const BaseArgument* length) const {
    space_->nextPoint(to, direction, length->getValue());
}

void Pattern::sharePoint(const std::string& point, const Pattern* pattern) const {
    const Point& p = space_->getPoint(point);
    pattern->addPoint(point, p.x(), p.y());
}

DartBuilder Pattern::startDart() const {
    return DartBuilder(outline_, new Dart(space_));
}

OutlineBuilder Pattern::editOutline() const {
    return OutlineBuilder(outline_);
}

// std::vector<Vertex> Pattern::getPoints() const {
//     return space_->getVBO();
// }

std::vector<std::vector<float>> Pattern::getOutline() const {
    return outline_->getPoints();
}

std::vector<float> Pattern::getShape() const {
    return outline_->getShape();
}
