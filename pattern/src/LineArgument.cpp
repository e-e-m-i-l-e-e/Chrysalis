#include "arguments/LineArgument.h"

#include "arguments/VectorFunctionArgument.h"

using namespace Chrysalis;

LineArgument::LineArgument(const args::point* origin, const args::number* angle)
    : origin_(origin), angle_(angle) {}

LineArgument::LineArgument(const args::point* origin, const args::point* destination)
    : origin_(origin), angle_(new VectorFunctionArgument::Angle(origin->clone(), destination->clone())) {}

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
