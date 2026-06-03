#ifndef CHRYSALIS_INSTRUCTIONSCONTAINER_H
#define CHRYSALIS_INSTRUCTIONSCONTAINER_H

#include <boost/optional/optional.hpp>

#include "../serialization.h"

#include "BaseInstructionsContainer.h"
#include "PatternInstructionsContainer.h"

namespace Chrysalis {
    class SERIALIZABLE(InstructionsContainer): public BaseInstructionsContainer<PatternInstructionsContainer> {};
    DEFAULT_SERIALIZE_MEMBERS(InstructionsContainer)
}

#endif //CHRYSALIS_INSTRUCTIONSCONTAINER_H