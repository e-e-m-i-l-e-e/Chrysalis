#ifndef CHRYSALIS_ACTIVEPATTERNSPACES_H
#define CHRYSALIS_ACTIVEPATTERNSPACES_H

#include "BaseArgument.h"
#include "SelectedPatterns.h"

namespace Chrysalis {
    class SERIALIZABLE(SelectedPatternsArgument): public BaseArgument<SelectedPatterns*> {
        PROVIDE_SERIALIZATION_ACCESS(SelectedPatternsArgument);
        explicit SelectedPatternsArgument() = default;
    public:
        explicit SelectedPatternsArgument(SelectedPatterns* patterns): BaseArgument(patterns) {};
    };
    DEFAULT_SERIALIZE_DERIVED_MEMBERS(SelectedPatternsArgument, BaseArgument<SelectedPatterns*>)
}

#endif //CHRYSALIS_ACTIVEPATTERNSPACES_H