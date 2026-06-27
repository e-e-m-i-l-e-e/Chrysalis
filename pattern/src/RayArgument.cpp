#include "arguments/RayArgument.h"

#include "arguments/BaseCalculatedArgument.h"

using namespace Chrysalis;

class RayArgument::AngleArgument: public BaseCalculatedArgument<double> {
public:
    explicit AngleArgument(const PointArgument* from, const PointArgument* to): from_(from), to_(to) {}

    bool isValid() const override {
        return from_->isValid() && to_->isValid();
    }
protected:
    double calculate() const override {
        return ProjectSpace::angle(*from_->get(), *to_->get());
    }
private:
    const PointArgument* from_;
    const PointArgument* to_;
};

RayArgument::RayArgument(const PointArgument* origin, const args::number* angle)
    : origin_(origin), angle_(angle) {}

RayArgument::RayArgument(const PointArgument* origin, const PointArgument* destination)
    : origin_(origin), angle_(new AngleArgument(origin, destination)) {}

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
