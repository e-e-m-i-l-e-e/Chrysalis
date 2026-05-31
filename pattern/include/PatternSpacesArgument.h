#ifndef CHRYSALIS_ACTIVEPATTERNSPACES_H
#define CHRYSALIS_ACTIVEPATTERNSPACES_H

#include "Argument.h"
#include "PatternSpace.h"

class PatternSpacesArgument: public Argument<std::list<Chrysalis::PatternSpace*>> {
public:
    explicit PatternSpacesArgument(const std::list<Chrysalis::PatternSpace*>& patternSpaces): Argument(patternSpaces) {}

    std::_List_const_iterator<std::_List_val<std::_List_simple_types<Chrysalis::PatternSpace*>>> begin();
    std::_List_const_iterator<std::_List_val<std::_List_simple_types<Chrysalis::PatternSpace*>>> end();

    void addPatternSpace(Chrysalis::PatternSpace* space);
};

#endif //CHRYSALIS_ACTIVEPATTERNSPACES_H