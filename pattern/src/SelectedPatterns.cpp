#include "SelectedPatterns.h"

using namespace Chrysalis;

std::list<PatternSpace*>::const_iterator SelectedPatterns::begin() const {
    return patterns_.cbegin();
}

std::list<PatternSpace*>::const_iterator SelectedPatterns::end() const {
    return patterns_.cend();
}
