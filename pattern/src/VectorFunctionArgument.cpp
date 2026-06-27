#include "arguments/VectorFunctionArgument.h"

Chrysalis::VectorFunctionArgument::VectorFunctionArgument(const name* pointFrom, const pattern* patternFrom,
                                                          const name* pointTo, const pattern* patternTo,
                                                          const VectorFunction* function)
    : pointFrom_(pointFrom), patternFrom_(patternFrom), pointTo_(pointTo), patternTo_(patternTo), function_(function) {}

Chrysalis::VectorFunctionArgument::~VectorFunctionArgument() {
    delete pointFrom_;
    delete patternFrom_;
    delete pointTo_;
    delete patternTo_;
    delete function_;
}

bool Chrysalis::VectorFunctionArgument::isValid() const {
    return !pointFrom_->isValid() || !patternFrom_->isValid() || !pointTo_->isValid() || !patternTo_->isValid() ||
           !patternFrom_->get()->hasPoint(pointFrom_->get()) || !patternTo_->get()->hasPoint(pointTo_->get());
}

double Chrysalis::VectorFunctionArgument::calculate() const {
    return function_->evaluate(pointFrom_, patternFrom_, pointTo_, patternTo_);
}