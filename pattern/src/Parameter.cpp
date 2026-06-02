#include "Parameter.h"

#include <iostream>
#include <utility>

using namespace Chrysalis;

Parameter::Parameter(std::string name): name_(std::move(name)) {}

bool Parameter::isValid() const {
    return value_.has_value() || defaultValue_.has_value();
}

bool Parameter::hasAlias() const {
    return alias_.has_value();
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

const std::string& Parameter::getName() const {
    return name_;
}

const std::string& Parameter::getAlias() const {
    return alias_.value();
}

void Parameter::setName(const std::string& name) {
    name_ = name;
}

void Parameter::setAlias(const std::string& alias) {
    alias_ = alias;
}

void Parameter::setValue(double value) {
    value_ = value;
}

void Parameter::setDefaultValue(double defaultValue) {
    defaultValue_ = defaultValue;
}