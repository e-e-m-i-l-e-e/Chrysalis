#include "arguments/SelectedNamesArgument.h"

void Chrysalis::SelectedNamesArgument::add(const std::string& name) {
    names_.push_back(name);
}

std::list<std::string>::const_iterator Chrysalis::SelectedNamesArgument::begin() const {
    return names_.cbegin();
}

std::list<std::string>::const_iterator Chrysalis::SelectedNamesArgument::end() const {
    return names_.cend();
}
