#include "arguments/RayArgument.h"

using namespace Chrysalis;

RayArgument::RayArgument(const args::point* origin, const args::point* destination)
    : LineArgument(origin, destination) {}

RayArgument::RayArgument(const args::point* origin, const args::number* angle)
    : LineArgument(origin, angle) {}

RayArgument::operator CG::Ray() const {
    return CG::Ray(*origin_->get(), static_cast<CG::Line>(*this));
}
