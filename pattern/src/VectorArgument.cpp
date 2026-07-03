#include "arguments/VectorArgument.h"

#include "arguments/VectorFunction.h"
#include "arguments/OriginPointArgument.h"
#include "arguments/VectorFunctionArgument.h"

using namespace Chrysalis;

VectorArgument::VectorArgument(const args::number* angle, const args::number* length): VectorArgument(new args::origin(), angle, length) {}

VectorArgument::VectorArgument(const args::point* origin, const args::number* length): VectorArgument(origin, new Argument<double>(0), length) {}

VectorArgument::VectorArgument(const args::point* origin, const args::number* angle, const args::number* length)
    : RayArgument(origin, angle), length_(length) {}

VectorArgument::VectorArgument(const args::point* origin, const args::point* destination)
    : RayArgument(origin, destination), length_(new VectorFunctionArgument(origin->clone(), destination->clone(), new VectorFunction::Length)) {}

VectorArgument::~VectorArgument() {
    delete length_;
}

bool VectorArgument::isValid() const {
    return RayArgument::isValid() && length_->isValid();
}

const args::number* VectorArgument::length() const {
    return length_;
}

VectorArgument::operator CG::Vector() const {
    return CG::Vector(static_cast<CG::Segment>(*this));
}

VectorArgument::operator CG::Segment() const {
    return CG::Segment(*origin()->get(), CG::relativePoint(*origin()->get(), angle_->get(), length_->get()));
}
