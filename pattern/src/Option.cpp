#include "Option.h"

using namespace Chrysalis;

Option::Option(const std::string& name): BaseNamedElement(name), Argument(false) {}

Option* Option::createDefault(const std::string& name, const bool isEnabled) {
    const auto option = new Option(name);
    option->set(isEnabled);
    return option;
}

void Option::toggle() {
    set(!get());
}
