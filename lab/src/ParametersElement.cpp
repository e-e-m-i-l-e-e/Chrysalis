#include "ParametersElement.h"

void Chrysalis::ParametersElement::setParameters(Parameters* parameters) {
    parameters_ = parameters;
    if (model_) model_->setParameters(parameters_);
}

Chrysalis::ParametersModel* Chrysalis::ParametersElement::getModel() const {
    return model_;
}

void Chrysalis::ParametersElement::setModel(ParametersModel* model) {
    model_ = model;
    model_->setParameters(parameters_);
}
