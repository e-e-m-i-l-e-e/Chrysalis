#include "Pattern.h"

Pattern::Pattern(const std::string& name, Space* space, Outline* outline)
    : name_(name), space_(space), outline_(outline) {}

void Pattern::addPoint(const std::string& name, const double x, const double y) const {
    space_->addPoint(name, x, y);
}

DartBuilder Pattern::startDart() const {
    return DartBuilder(new Dart(space_));
}

OutlineBuilder Pattern::startOutline() const {
    return OutlineBuilder(outline_);
}

std::vector<float> Pattern::getPoints() const {
    return space_->getPoints();
}

std::vector<float> Pattern::getOutline() const {
    return outline_->getPoints();
}
