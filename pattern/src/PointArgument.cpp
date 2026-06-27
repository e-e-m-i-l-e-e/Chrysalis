#include "arguments/PointArgument.h"

using namespace Chrysalis;

PointArgument::PointArgument(const args::name* name, const args::patterns* patterns)
    : name_(name), patterns_(patterns) {}

PointArgument::~PointArgument() {
    delete name_;
    delete patterns_;
}

bool PointArgument::isValid() const {
    return name_->isValid() && !patterns_->empty() && patterns_->all(&PatternSpace::hasPoint, name_->get());
}

const Point* PointArgument::get() const {
    return patterns_->onAny(&PatternSpace::getPoint, name_->get());
}

const std::string& PointArgument::getName() const {
    return name_->get();
}
