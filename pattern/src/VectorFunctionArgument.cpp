#include "VectorFunctionArgument.h"

#include <utility>

using namespace Chrysalis;

double VectorFunctionArgument::Use::ANGLE(const VectorFunctionArgument* function) {
    // return function->space->angle(function->from, function->to);
    return 0;
}

double VectorFunctionArgument::Use::LENGTH(const VectorFunctionArgument* function) {
    // return function->space->distance(function->from, function->to);
    return 0;
}

VectorFunctionArgument::VectorFunctionArgument(ProjectSpace* space, std::string from, std::string to, double(*function)(const VectorFunctionArgument*))
    : space(space), from(std::move(from)), to(std::move(to)), function(function) {
    argument_ = (*function)(this);
}
