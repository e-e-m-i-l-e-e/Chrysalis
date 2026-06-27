#ifndef CHRYSALIS_ACTIVEPATTERNSPACES_H
#define CHRYSALIS_ACTIVEPATTERNSPACES_H

#include "BaseArgumentOld.h"
#include "SelectedPatterns.h"

namespace Chrysalis {
    class SERIALIZABLE(SelectedPatternsArgument): public BaseArgumentOld<SelectedPatterns*> {
        PROVIDE_SERIALIZATION_ACCESS(SelectedPatternsArgument);
        explicit SelectedPatternsArgument() = default;
    public:
        explicit SelectedPatternsArgument(SelectedPatterns* patterns): BaseArgumentOld(patterns) {};
    };
    DEFAULT_SERIALIZE_DERIVED_MEMBERS(SelectedPatternsArgument, BaseArgumentOld<SelectedPatterns*>)
}

#endif //CHRYSALIS_ACTIVEPATTERNSPACES_H