#include "arguments/ParameterArgument.h"

using namespace Chrysalis;

ParameterArgument::ParameterArgument(Parameter* parameter): parameter_(parameter) {}

std::expected<double, Error> ParameterArgument::calculate() const {
    if (parameter_->hasValue()) {
        return parameter_->getValue();
    } else if (parameter_->hasDefaultValue()) {
        return parameter_->getDefaultValue();
    }
    return std::unexpected(Error{"Empty parameter"});
}