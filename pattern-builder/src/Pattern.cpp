#include "Pattern.h"

Pattern::Pattern(const std::string& name, Space* space, Outline* outline)
    : name_(name), space_(space), outline_(outline) {}

void Pattern::addPoint(const std::string& name, const double x, const double y) const {
    space_->addPoint(name, x, y);
}

DartBuilder Pattern::startDart() const {
    return DartBuilder(outline_, new Dart(space_));
}

OutlineBuilder Pattern::editOutline() const {
    return OutlineBuilder(outline_);
}

std::vector<Vertex> Pattern::getPoints() const {
    return space_->getVBO();
}

std::vector<std::vector<float>> Pattern::getOutline() const {
    return outline_->getPoints();
}

std::vector<float> Pattern::getShape() const {
    return outline_->getShape();
}
