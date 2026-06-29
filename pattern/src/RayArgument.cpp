#include "arguments/RayArgument.h"

using namespace Chrysalis;

RayArgument::RayArgument(const PointArgument* origin, const PointArgument* destination)
    : LineArgument(origin, destination) {}

RayArgument::RayArgument(const PointArgument* origin, const args::number* angle)
    : LineArgument(origin, angle) {}

RayArgument::operator CGAL::Ray() const {
    return CGAL::Ray(*origin_->get(), static_cast<CGAL::Line>(*this));
}
