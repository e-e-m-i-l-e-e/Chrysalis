#include "arguments/PointArgument.h"

using namespace Chrysalis;

PointArgument::PointArgument(const args::name* pointName, const PatternArgument* pattern)
    : pointName_(pointName), pattern_(pattern) {}

PointArgument::~PointArgument() {
    delete pointName_;
    delete pattern_;
}

bool PointArgument::isValid() const {
    return pattern_->isValid() && pointName_->isValid() && pattern_->get()->hasPoint(pointName_->get());
}

const Point* PointArgument::get() const {
    return pattern_->get()->getPoint(pointName_->get());
}

const std::string& PointArgument::getName() const {
    return pointName_->get();
}
