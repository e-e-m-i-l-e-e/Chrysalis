#include "VectorFunction.h"

double VectorFunction::ANGLE(const VectorFunction* function) {
    return function->space->angle(function->from, function->to);
}

double VectorFunction::LENGTH(const VectorFunction* function) {
    return function->space->distance(function->from, function->to);
}

VectorFunction::VectorFunction(Space* space, const std::string& from, const std::string& to, double(*function)(const VectorFunction*))
    : space(space), from(from), to(to), function(function) {}

double VectorFunction::getValue() const {
    return (*function)(this);
}
