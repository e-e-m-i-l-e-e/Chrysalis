#include "arguments/ParameterArgument.h"

#include <iostream>
#include <ostream>

using namespace Chrysalis;

ParameterArgument::ParameterArgument(Parameter* parameter)
    : NumberArgument([&] -> boost::optional<double> {
        if (parameter->hasValue()) return parameter->getValue();
        if (parameter->hasDefaultValue()) return parameter->getDefaultValue();
        return boost::none;
    }()), parameter_(parameter) {
    observe(parameter);
}

void ParameterArgument::valueChanged() {
    if (parameter_->hasValue()) setArgument(parameter_->getValue());
    else if (parameter_->hasDefaultValue()) setArgument(parameter_->getDefaultValue());
    else resetArgument();
}
