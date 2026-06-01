#ifndef CHRYSALIS_PATTERNARGUMENT_H
#define CHRYSALIS_PATTERNARGUMENT_H

#include "Argument.h"
#include "PatternSpace.h"

namespace Chrysalis {
    class PatternArgument: public Argument<PatternSpace*> {
    public:
        explicit PatternArgument() = default;
        explicit PatternArgument(PatternSpace* pattern): Argument(pattern) {}
    };
}

#endif //CHRYSALIS_PATTERNARGUMENT_H
