#include "arguments/VectorArgument.h"

#include "arguments/BaseCalculatedArgument.h"

using namespace Chrysalis;

class VectorArgument::LengthArgument: public BaseCalculatedArgument<double> {
public:
    explicit LengthArgument(const PointArgument* from, const PointArgument* to): from_(from), to_(to) {}

    bool isValid() const override {
        return from_->isValid() && to_->isValid();
    }
protected:
    double calculate() const override {
        return CG::length(*from_->get(), *to_->get());
    }
private:
    const PointArgument* from_;
    const PointArgument* to_;
};

VectorArgument::VectorArgument(const PointArgument* origin, const args::number* angle, const args::number* length)
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

VectorArgument::operator CG::Vector() const {
    return CG::Vector(static_cast<CG::Segment>(*this));
}

VectorArgument::operator CG::Segment() const {
    return CG::Segment(*origin()->get(), CG::relativePoint(*origin()->get(), angle_->get(), length_->get()));
}
