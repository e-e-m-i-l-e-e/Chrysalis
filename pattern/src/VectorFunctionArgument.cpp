#include "arguments/VectorFunctionArgument.h"

Chrysalis::VectorFunctionArgument::VectorFunctionArgument(const args::point* from, const args::point* to,
                                                          const VectorFunction* function)
    : from_(from), to_(to), function_(function) {}

Chrysalis::VectorFunctionArgument::~VectorFunctionArgument() {
    delete from_;
    delete to_;
}

bool Chrysalis::VectorFunctionArgument::isValid() const {
    return from_->isValid() && to_->isValid();
}

double Chrysalis::VectorFunctionArgument::calculate() const {
    return function_->evaluate(from_, to_);
}