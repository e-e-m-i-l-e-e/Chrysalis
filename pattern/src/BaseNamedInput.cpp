#include "BaseNamedInput.h"

using namespace Chrysalis;

BaseNamedInput::BaseNamedInput(const std::string& name): name_(name) {}

bool BaseNamedInput::hasAlias() const {
    return alias_.has_value();
}

const std::string& BaseNamedInput::getName() const {
    return name_;
}

const std::string& BaseNamedInput::getAlias() const {
    return alias_.get();
}

void BaseNamedInput::setName(const std::string& name) {
    name_ = name;
}

void BaseNamedInput::setAlias(const std::string& alias) {
    alias_ = alias;
}
