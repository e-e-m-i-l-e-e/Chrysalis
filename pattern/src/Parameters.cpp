#include "Parameters.h"

#include <ranges>

using namespace Chrysalis;

Parameters::~Parameters() {
    for (const auto& parameter: parameters_) {
        delete parameter;
    }
}

Parameter* Parameters::at(const int index) {
    return *std::next(parameters_.begin(), index);
}

int Parameters::count() const {
    return static_cast<int>(parameters_.size());
}

void Parameters::addParameter(Parameter* parameter) {
    parameters_.push_back(parameter);
    parametersMap_[parameter->getName()] = parameter;
    if (parameter->hasAlias()) {
        parametersMap_[parameter->getAlias()] = parameter;
    }
}

Parameter* Parameters::getParameter(const std::string& name) const {
    return parametersMap_.at(name);
}
