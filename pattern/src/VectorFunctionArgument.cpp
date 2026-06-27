#include "arguments/VectorFunctionArgument.h"

Chrysalis::VectorFunctionArgument::VectorFunctionArgument(const name* pointFrom, const pattern* patternFrom,
                                                          const name* pointTo, const pattern* patternTo,
                                                          const VectorFunction* function)
    : NumberArgument(function->evaluate(pointFrom, patternFrom, pointTo, patternTo)), pointFrom_(pointFrom),
      patternFrom_(patternFrom), pointTo_(pointTo), patternTo_(patternTo), function_(function) {}

Chrysalis::VectorFunctionArgument::~VectorFunctionArgument() {
    delete pointFrom_;
    delete patternFrom_;
    delete pointTo_;
    delete patternTo_;
    delete function_;
}


bool Chrysalis::VectorFunctionArgument::hasValue() const {
    return !pointFrom_->hasValue() || !patternFrom_->hasArgument() || !pointTo_->hasValue() || !patternTo_->hasArgument() ||
           !patternFrom_->getArgument()->hasPoint(pointFrom_->get()) || !patternTo_->getArgument()->hasPoint(pointTo_->get());
}

double Chrysalis::VectorFunctionArgument::get() const {
    return function_->evaluate(pointFrom_, patternFrom_, pointTo_, patternTo_);
}