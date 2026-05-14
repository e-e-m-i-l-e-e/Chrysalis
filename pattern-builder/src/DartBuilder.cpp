#include "DartBuilder.h"

DartBuilder::DartBuilder(Outline* outline, Dart* dart): outline_(outline), dart_(dart) {}

DartBuilder& DartBuilder::addPoint(const std::string& pointName) {
    dart_->addPoint(pointName);
    return *this;
}

void DartBuilder::complete() const {
    outline_->addDart(dart_);
}
