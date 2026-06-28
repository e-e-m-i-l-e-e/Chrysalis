#ifndef CHRYSALIS_INSTRUCTIONSCONTAINER_H
#define CHRYSALIS_INSTRUCTIONSCONTAINER_H

#include <boost/optional/optional.hpp>

#include "serialization.h"

#include "BaseInstructionsContainer.h"
#include "PatternInstructionsContainer.h"

namespace Chrysalis {
    class InstructionsContainer: public BaseInstructionsContainer<PatternInstructionsContainer> {
        SERIALIZE_DERIVED_FROM(BaseInstructionsContainer)
    };
}

#endif //CHRYSALIS_INSTRUCTIONSCONTAINER_H