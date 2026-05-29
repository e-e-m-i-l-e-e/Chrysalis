#include "Parameters.h"

#include <ranges>

using namespace Chrysalis;

Parameters::~Parameters() {
    for (const auto& parameter: parameters_ | std::views::values) {
        delete parameter;
    }
}

Parameter* Parameters::at(int index) {
    return std::next(parameters_.begin(), index)->second;
}

unsigned int Parameters::count() const {
    return parameters_.size();
}

void Parameters::addParameter(Parameter* parameter) {
    parameters_[parameter->getName()] = parameter;
}

Parameter* Parameters::getParameter(const std::string& name) {
    return parameters_[name];
}
