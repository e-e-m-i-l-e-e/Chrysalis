#include "arguments/RayArgument.h"

#include "arguments/AngleArgument.h"
#include "arguments/BaseCalculatedArgument.h"

using namespace Chrysalis;

RayArgument::RayArgument(const PointArgument* origin, const num* angle)
    : origin_(origin), angle_(angle) {}

RayArgument::RayArgument(const PointArgument* origin, const PointArgument* destination) : origin_(origin), angle_(new AngleArgument(origin, destination)) {}

RayArgument::~RayArgument() {
    delete origin_;
    delete angle_;
}

bool RayArgument::isValid() const {
    return origin_->isValid() && angle_->isValid();
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
