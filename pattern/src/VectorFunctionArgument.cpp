#include "VectorFunctionArgument.h"

#include <utility>

double VectorFunctionArgument::Use::ANGLE(const VectorFunctionArgument* function) {
    return function->space->angle(function->from, function->to);
}

double VectorFunctionArgument::Use::LENGTH(const VectorFunctionArgument* function) {
    return function->space->distance(function->from, function->to);
}

VectorFunctionArgument::VectorFunctionArgument(Space* space, std::string from, std::string to, double(*function)(const VectorFunctionArgument*))
    : space(space), from(std::move(from)), to(std::move(to)), function(function) {
    argument_ = (*function)(this);
}
