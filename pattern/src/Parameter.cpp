#include "Parameter.h"

using namespace Chrysalis;

Parameter::Parameter(const std::string& name, const double value): value_(value), name_(name) {}

double Parameter::getValue() const {
    return value_;
}

void Parameter::setValue(const double value) {
    value_ = value;
}

const std::string& Parameter::getName() const {
    return name_;
}
