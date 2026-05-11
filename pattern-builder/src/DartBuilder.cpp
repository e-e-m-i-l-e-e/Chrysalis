#include "DartBuilder.h"

DartBuilder::DartBuilder(Dart* dart): dart_(dart) {}

DartBuilder& DartBuilder::addPoint(const std::string& pointName) {
    dart_->addPoint(pointName);
    return *this;
}
