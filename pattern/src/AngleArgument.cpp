#include "arguments/AngleArgument.h"

using namespace Chrysalis;

AngleArgument::AngleArgument(const PointArgument* from, const PointArgument* to): from_(from), to_(to) {}

bool AngleArgument::isValid() const {
    return from_->isValid() && to_->isValid();
}

double AngleArgument::calculate() const {
    return ProjectSpace::angle(*from_->get(), *to_->get());
}
