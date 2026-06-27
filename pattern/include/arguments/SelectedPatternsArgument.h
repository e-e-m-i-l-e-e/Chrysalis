#ifndef CHRYSALIS_ACTIVEPATTERNSPACES_H
#define CHRYSALIS_ACTIVEPATTERNSPACES_H

#include <boost/serialization/export.hpp>

#include "SelectedPatterns.h"
#include "arguments/BaseValidArgument.h"

namespace Chrysalis {
    class SelectedPatternsArgument: public BaseValidArgument<SelectedPatterns*> {
    public:
        explicit SelectedPatternsArgument(): BaseValidArgument<SelectedPatterns*>(nullptr) {}
        explicit SelectedPatternsArgument(SelectedPatterns* patterns): BaseValidArgument(patterns) {};
    };
    SERIALIZE_DERIVED_MEMBERS(SelectedPatternsArgument, BaseValidArgument<SelectedPatterns*>)
}

#endif //CHRYSALIS_ACTIVEPATTERNSPACES_H