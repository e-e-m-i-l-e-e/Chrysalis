#include "PatternSpacesArgument.h"

std::_List_const_iterator<std::_List_val<std::_List_simple_types<Chrysalis::PatternSpace*>>> PatternSpacesArgument::begin() {
    return argument_->cbegin();
}

std::_List_const_iterator<std::_List_val<std::_List_simple_types<Chrysalis::PatternSpace*>>> PatternSpacesArgument::end() {
    return argument_->cend();
}

void PatternSpacesArgument::addPatternSpace(Chrysalis::PatternSpace* space)
{
}
