#include "Parameter.h"

#include <iostream>
#include <utility>

using namespace Chrysalis;

Parameter::Parameter(const std::string& name): BaseNamedElement(name) {}

Parameter* Parameter::create(const std::string& name, const double value) {
    const auto parameter = new Parameter(name);
    parameter->setValue(value);
    return parameter;
}

Parameter* Parameter::createDefault(const std::string& name, const double defaultValue) {
    const auto parameter = new Parameter(name);
    parameter->setDefaultValue(defaultValue);
    return parameter;
}

bool Parameter::isValid() const {
    return value_.has_value() || defaultValue_.has_value();
}

bool Parameter::hasValue() const {
    return value_.has_value();
}

bool Parameter::hasDefaultValue() const {
    return defaultValue_.has_value();
}

double Parameter::getValue() const {
    return value_.value();
}

double Parameter::getDefaultValue() const {
    return defaultValue_.value();
}

void Parameter::setValue(double value) {
    value_ = value;
    notify(&ParameterObserver::valueChanged, value);
}

void Parameter::setDefaultValue(double defaultValue) {
    defaultValue_ = defaultValue;
}