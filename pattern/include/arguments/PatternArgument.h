#ifndef CHRYSALIS_PATTERNARGUMENT_H
#define CHRYSALIS_PATTERNARGUMENT_H

#include "BaseArgumentOld.h"
#include "PatternSpace.h"

namespace Chrysalis {
    class SERIALIZABLE(PatternArgument): public BaseArgumentOld<PatternSpace*> {
    public:
        explicit PatternArgument() = default;
        explicit PatternArgument(PatternSpace* pattern): BaseArgumentOld(pattern) {}
    };
    DEFAULT_SERIALIZE_DERIVED_MEMBERS(PatternArgument, BaseArgumentOld<PatternSpace*>)
}

#endif //CHRYSALIS_PATTERNARGUMENT_H
