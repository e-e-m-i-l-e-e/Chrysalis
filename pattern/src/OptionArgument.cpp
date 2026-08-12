#include "arguments/OptionArgument.h"

using namespace Chrysalis;

OptionArgument::OptionArgument(const OptionsContainer* options, const args::name* name)
    : options_(options), name_(name) {}

OptionArgument::~OptionArgument() {
    delete name_;
}

std::expected<bool, Error> OptionArgument::calculate() const {
    return name_->get().transform([this](const std::string& name) {
        return options_->get(name)->get().value().value;
    });
}
