#include "ProjectParameters.h"

#include <ranges>

ProjectParameters::~ProjectParameters() {
    for (const auto& parameter: parameters_ | std::views::values) {
        delete parameter;
    }
}

void ProjectParameters::addParameter(Parameter* parameter) {
    parameters_[parameter->getName()] = parameter;
}

Parameter* ProjectParameters::getParameter(const std::string& name) {
    return parameters_[name];
}
