#include "arguments/VectorArgument.h"

#include "arguments/OriginPointArgument.h"
#include "arguments/VectorFunctionArgument.h"

using namespace Chrysalis;

VectorArgument::VectorArgument(args::number&& angle, args::number&& length): VectorArgument(new args::origin(), std::move(angle), std::move(length)) {}

VectorArgument::VectorArgument(const args::point* origin, args::number&& length): VectorArgument(origin, std::make_unique<Argument<double>>(0), std::move(length)) {}

VectorArgument::VectorArgument(const args::point* origin, args::number&& angle, args::number&& length)
    : RayArgument(std::move(origin), std::move(angle)), length_(std::move(length)) {}

VectorArgument::VectorArgument(const args::point* origin, const args::point* destination)
    : RayArgument(origin, destination), length_(new VectorFunctionArgument::Length(origin->clone(), destination->clone())) {}

bool VectorArgument::isValid() const {
    return RayArgument::isValid();
}

const args::number& VectorArgument::length() const {
    return length_;
}

VectorArgument::operator CG::Vector() const {
    return CG::Vector(static_cast<CG::Segment>(*this));
}

VectorArgument::operator CG::Segment() const {
    return CG::Segment(*origin(), CG::relativePoint(*origin(), angle_->get().value(), length_->get().value()));
}
