#include "arguments/VectorFunctionArgument.h"

using namespace Chrysalis;

VectorFunctionArgument::VectorFunctionArgument(const args::point* from, const args::point* to)
    : from_(from), to_(to) {}

VectorFunctionArgument::~VectorFunctionArgument() {
    delete from_;
    delete to_;
}

std::expected<double, Error> VectorFunctionArgument::calculate() const {
    return evaluate(*from_->get(), *to_->get());
}

std::expected<double, Error> VectorFunctionArgument::Length::evaluate(const CG::Point& from, const CG::Point& to) const {
    return CG::length(from, to);
}

std::expected<double, Error> VectorFunctionArgument::Angle::evaluate(const CG::Point& from, const CG::Point& to) const {
    return CG::angle(from, to);
}