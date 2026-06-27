#ifndef CHRYSALIS_PATTERNSCONTAINERARGUMENT_H
#define CHRYSALIS_PATTERNSCONTAINERARGUMENT_H

#include "PatternSpace.h"
#include "arguments/BaseContainerArgument.h"

namespace Chrysalis {
    class PatternsContainerArgument: public BaseContainerArgument<PatternSpace> {
        SERIALIZE_DERIVED_FROM(BaseContainerArgument)
    };
    namespace args {
        using patterns = PatternsContainerArgument;
    }
}

#endif //CHRYSALIS_PATTERNSCONTAINERARGUMENT_H