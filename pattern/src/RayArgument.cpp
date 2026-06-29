#include "arguments/RayArgument.h"

using namespace Chrysalis;

RayArgument::RayArgument(const PointArgument* origin, const PointArgument* destination)
    : LineArgument(origin, destination) {}

RayArgument::RayArgument(const PointArgument* origin, const args::number* angle)
    : LineArgument(origin, angle) {}

RayArgument::operator CG::Ray() const {
    return CG::Ray(*origin_->get(), static_cast<CG::Line>(*this));
}
