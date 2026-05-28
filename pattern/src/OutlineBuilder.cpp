#include "OutlineBuilder.h"

using namespace PB;

OutlineBuilder::OutlineBuilder(Outline* outline): outline_(outline) {}

OutlineBuilder& OutlineBuilder::addPoint(const std::string& pointName) {
    outline_->addPoint(pointName);
    return *this;
}
