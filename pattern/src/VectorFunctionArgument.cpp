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