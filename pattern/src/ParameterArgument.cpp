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
    parameter->addObserver(this);
}

void ParameterArgument::valueChanged(const double value) {
    setArgument(value);
}
