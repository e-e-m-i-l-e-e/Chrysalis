#ifndef CHRYSALIS_PATTERNSPACESARGUMENT_H
#define CHRYSALIS_PATTERNSPACESARGUMENT_H

#include "Argument.h"
#include "PatternSpace.h"

class PatternSpacesArgument: public Argument<std::forward_list<PatternSpace*>> {
public:
    template<typename... Spaces>
    explicit PatternSpacesArgument(Spaces*... patternSpaces): Argument(patternSpaces...) {}

    void addPatternSpace(PatternSpace* space);
};

#endif //CHRYSALIS_PATTERNSPACESARGUMENT_H