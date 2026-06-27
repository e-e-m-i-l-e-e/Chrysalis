#include "arguments/VectorArgument.h"

#include "arguments/LengthArgument.h"

using namespace Chrysalis;

VectorArgument::VectorArgument(const PointArgument* origin, const num* angle, const num* length)
    : RayArgument(origin, angle), length_(length) {}

VectorArgument::VectorArgument(const PointArgument* origin, const PointArgument* destination)
: RayArgument(origin, destination), length_(new LengthArgument(origin, destination)) {}

VectorArgument::~VectorArgument() {
    delete length_;
}

bool VectorArgument::isValid() const {
    return RayArgument::isValid() && length_->isValid();
}

double VectorArgument::getLength() const {
    return length_->get();
}