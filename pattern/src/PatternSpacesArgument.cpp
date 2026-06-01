#include "PatternSpacesArgument.h"

std::list<Chrysalis::PatternSpace*>::const_iterator PatternSpacesArgument::begin() {
    return argument_->cbegin();
}

std::list<Chrysalis::PatternSpace*>::const_iterator PatternSpacesArgument::end() {
    return argument_->cend();
}

void PatternSpacesArgument::addPatternSpace(Chrysalis::PatternSpace* space)
{
}
