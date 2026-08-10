#include "arguments/OptionArgument.h"

using namespace Chrysalis;

OptionArgument::OptionArgument(const OptionsContainer* options, const args::name* name)
    : options_(options), name_(name) {}

OptionArgument::~OptionArgument() {
    delete name_;
}

bool OptionArgument::isValid() const {
    return options_->has(name_->get());
}

bool OptionArgument::calculate() const {
    return options_->get(name_->get())->get().value;
}
