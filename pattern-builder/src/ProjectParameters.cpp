#include "ProjectParameters.h"

ProjectParameters::~ProjectParameters() {
    for (const auto& parameter : parameters_) {
        delete parameter;
    }
}

void ProjectParameters::addParameter(Parameter* parameter) {
    parameters_.push_back(parameter);
}
