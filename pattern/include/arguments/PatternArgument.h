#ifndef CHRYSALIS_PATTERNARGUMENT_H
#define CHRYSALIS_PATTERNARGUMENT_H

#include "BaseArgument.h"
#include "PatternSpace.h"

namespace Chrysalis {
    class SERIALIZABLE(PatternArgument): public BaseArgument<PatternSpace*> {
    public:
        explicit PatternArgument() = default;
        explicit PatternArgument(PatternSpace* pattern): BaseArgument(pattern) {}
    };
    DEFAULT_SERIALIZE_DERIVED_MEMBERS(PatternArgument, BaseArgument<PatternSpace*>)
}

#endif //CHRYSALIS_PATTERNARGUMENT_H
