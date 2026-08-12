#include "arguments/PatternPointArgument.h"

using namespace Chrysalis;

PatternPointArgument::PatternPointArgument(const args::name* name, const args::patterns* patterns)
    : name_(name), patterns_(patterns) {}

PatternPointArgument::PatternPointArgument(const PatternPointArgument& other)
    : name_(new args::name(*other.name())), patterns_(new args::patterns(*other.patterns_)) {}

PatternPointArgument::~PatternPointArgument() {
    delete name_;
    delete patterns_;
}

BasePointArgument* PatternPointArgument::clone() const {
    return new PatternPointArgument(*this);
}

bool PatternPointArgument::isValid() const {
    return !patterns_->empty() && patterns_->all(&PatternSpace::hasPoint, name_->get().value());
}

const Point* PatternPointArgument::get() const {
    return patterns_->onAny(&PatternSpace::getPoint, name_->get().value());
}

const args::name* PatternPointArgument::name() const {
    return name_;
}

PatternPointArgument::operator CG::Point() const {
    return patterns_->onAny(&PatternSpace::getTransformation).apply(*this->get());
}