#ifndef CHRYSALIS_ACTIVEPATTERNSPACES_H
#define CHRYSALIS_ACTIVEPATTERNSPACES_H

#include "Argument.h"
#include "PatternSpace.h"

class PatternSpacesArgument: public Argument<std::list<Chrysalis::PatternSpace*>> {
public:
    explicit PatternSpacesArgument(const std::list<Chrysalis::PatternSpace*>& patternSpaces): Argument(patternSpaces) {}

    std::list<Chrysalis::PatternSpace*>::const_iterator begin();
    std::list<Chrysalis::PatternSpace*>::const_iterator end();

    void addPatternSpace(Chrysalis::PatternSpace* space);
};

#endif //CHRYSALIS_ACTIVEPATTERNSPACES_H