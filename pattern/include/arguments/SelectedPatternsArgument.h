#ifndef CHRYSALIS_ACTIVEPATTERNSPACES_H
#define CHRYSALIS_ACTIVEPATTERNSPACES_H

#include "BaseArgument.h"
#include "SelectedPatterns.h"

namespace Chrysalis {
    class SelectedPatternsArgument: public BaseArgument<SelectedPatterns*> {
    public:
        explicit SelectedPatternsArgument(SelectedPatterns* patterns): BaseArgument(patterns) {};
    };
}

#endif //CHRYSALIS_ACTIVEPATTERNSPACES_H