#include "BaseNamedElement.h"

using namespace Chrysalis;

BaseNamedElement::BaseNamedElement(const std::string& name): name_(name) {}

bool BaseNamedElement::hasAlias() const {
    return alias_.has_value();
}

const std::string& BaseNamedElement::getName() const {
    return name_;
}

const std::string& BaseNamedElement::getAlias() const {
    return alias_.get();
}

void BaseNamedElement::setName(const std::string& name) {
    name_ = name;
}

void BaseNamedElement::setAlias(const std::string& alias) {
    alias_ = alias;
}
