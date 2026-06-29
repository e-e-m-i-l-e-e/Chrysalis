#include "arguments/LineArgument.h"
#include "arguments/BaseCalculatedArgument.h"

using namespace Chrysalis;

class LineArgument::AngleArgument: public BaseCalculatedArgument<double> {
public:
    explicit AngleArgument(const PointArgument* from, const PointArgument* to): from_(from), to_(to) {}

    bool isValid() const override {
        return from_->isValid() && to_->isValid();
    }
protected:
    double calculate() const override {
        return CG::angle(*from_->get(), *to_->get());
    }
private:
    const PointArgument* from_;
    const PointArgument* to_;
};

LineArgument::LineArgument(const PointArgument* origin, const args::number* angle)
    : origin_(origin), angle_(angle) {}

LineArgument::LineArgument(const PointArgument* origin, const PointArgument* destination)
    : origin_(origin), angle_(new AngleArgument(origin, destination)) {}

LineArgument::~LineArgument() {
    delete origin_;
    delete angle_;
}

bool LineArgument::isValid() const {
    return origin_->isValid() && angle_->isValid();
}

const args::number* LineArgument::angle() const {
    return angle_;
}

const args::point* LineArgument::origin() const {
    return origin_;
}

LineArgument::operator CG::Line() const {
    return CG::Line(*origin_->get(), CG::Vector(CG::cos(CG::radians(angle_->get())), CG::sin(CG::radians(angle_->get()))));
}
