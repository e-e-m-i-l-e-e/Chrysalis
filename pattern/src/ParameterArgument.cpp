#include "arguments/ParameterArgument.h"

#include <iostream>
#include <ostream>

using namespace Chrysalis;

ParameterArgument::ParameterArgument(Parameter* parameter): parameter_(parameter) {}

bool ParameterArgument::hasValue() const {
    return parameter_->hasValue() || parameter_->hasDefaultValue();
}

double ParameterArgument::get() const {
    return parameter_->hasValue() ? parameter_->getValue() : parameter_->getDefaultValue();
}