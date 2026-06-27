#include "arguments/PointArgument.h"

using namespace Chrysalis;

PointArgument::PointArgument(const NameArgument* name, const PatternArgument* pattern)
    : name_(name), pattern_(pattern) {}

PointArgument::~PointArgument() {
    delete name_;
    delete pattern_;
}

bool PointArgument::isValid() const {
    return pattern_->hasArgument() && name_->hasValue() && pattern_->getArgument()->hasPoint(name_->get());
}

const Point* PointArgument::get() const {
    return pattern_->getArgument()->getPoint(name_->get());
}

const std::string& PointArgument::getName() const {
    return name_->get();
}
