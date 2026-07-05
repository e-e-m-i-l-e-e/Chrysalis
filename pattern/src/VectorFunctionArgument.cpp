#include "arguments/VectorFunctionArgument.h"

Chrysalis::VectorFunctionArgument::VectorFunctionArgument(const args::point* from, const args::point* to)
    : from_(from), to_(to) {}

Chrysalis::VectorFunctionArgument::~VectorFunctionArgument() {
    delete from_;
    delete to_;
}

bool Chrysalis::VectorFunctionArgument::isValid() const {
    return from_->isValid() && to_->isValid();
}

double Chrysalis::VectorFunctionArgument::calculate() const {
    return evaluate(*from_->get(), *to_->get());
}

double Chrysalis::VectorFunctionArgument::Length::evaluate(const CG::Point& from, const CG::Point& to) const {
    return CG::length(from, to);
}

double Chrysalis::VectorFunctionArgument::Angle::evaluate(const CG::Point& from, const CG::Point& to) const {
    return CG::angle(from, to);
}