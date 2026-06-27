#include "arguments/LengthArgument.h"

Chrysalis::LengthArgument::LengthArgument(const PointArgument* from, const PointArgument* to): from_(from), to_(to) {}

bool Chrysalis::LengthArgument::isValid() const {
    return from_->isValid() && to_->isValid();
}

double Chrysalis::LengthArgument::calculate() const {
    return ProjectSpace::length(*from_->get(), *to_->get());
}
