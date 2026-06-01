#ifndef CHRYSALIS_PATTERNARGUMENT_H
#define CHRYSALIS_PATTERNARGUMENT_H

#include "BaseArgument.h"
#include "PatternSpace.h"

namespace Chrysalis {
    class PatternArgument: public BaseArgument<PatternSpace*> {
    public:
        explicit PatternArgument() = default;
        explicit PatternArgument(PatternSpace* pattern): BaseArgument(pattern) {}
    };
}

#endif //CHRYSALIS_PATTERNARGUMENT_H
