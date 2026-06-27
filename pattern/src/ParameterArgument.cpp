#include "arguments/ParameterArgument.h"

using namespace Chrysalis;

ParameterArgument::ParameterArgument(Parameter* parameter): parameter_(parameter) {}

bool ParameterArgument::isValid() const {
    return parameter_->hasValue() || parameter_->hasDefaultValue();
}

double ParameterArgument::calculate() const {
    return parameter_->hasValue() ? parameter_->getValue() : parameter_->getDefaultValue();
}