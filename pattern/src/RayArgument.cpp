#include "arguments/RayArgument.h"

using namespace Chrysalis;

RayArgument::RayArgument(const PointArgument* origin, const NumberArgument* angle)
    : origin_(origin), angle_(angle) {}

RayArgument::RayArgument(const PointArgument* origin, const PointArgument* destination) : origin_(origin), angle_([&] {
    if (origin->isValid() && destination->isValid()) {
        return new NumberArgument(ProjectSpace::angle(*origin->get(), *destination->get()));
    }
    return new NumberArgument();
}()) {}

RayArgument::~RayArgument() {
    delete origin_;
    delete angle_;
}

bool RayArgument::isValid() const {
    return origin_->isValid() && angle_->hasValue();
}

double RayArgument::getAngle() const {
    return angle_->get();
}

const Point* RayArgument::getOrigin() const {
    return origin_->get();
}

const std::string& RayArgument::getOriginName() const {
    return origin_->getName();
}
