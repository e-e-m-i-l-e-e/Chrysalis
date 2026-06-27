#include "arguments/VectorArgument.h"

using namespace Chrysalis;

VectorArgument::VectorArgument(const PointArgument* origin, const NumberArgument* angle, const NumberArgument* length)
    : RayArgument(origin, angle), length_(length) {}

VectorArgument::VectorArgument(const PointArgument* origin, const PointArgument* destination)
: RayArgument(origin, destination), length_([&] {
    if (origin->isValid() && destination->isValid()) {
        return new NumberArgument(ProjectSpace::length(*origin->get(), *destination->get()));
    }
    return new NumberArgument();
}()) {}

VectorArgument::~VectorArgument() {
    delete length_;
}

bool VectorArgument::isValid() const {
    return RayArgument::isValid() && length_->hasValue();
}

double VectorArgument::getLength() const {
    return length_->get();
}