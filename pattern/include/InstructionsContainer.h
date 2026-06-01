#ifndef CHRYSALIS_INSTRUCTIONSCONTAINER_H
#define CHRYSALIS_INSTRUCTIONSCONTAINER_H

#include "serialization.h"

#include "BaseContainer.h"
#include "PatternInstructionsContainer.h"

namespace Chrysalis {
    class SERIALIZABLE(InstructionsContainer): public BaseContainer<PatternInstructionsContainer> {
    public:
        void execute() const;
    };
    DEFAULT_SERIALIZE_MEMBERS(InstructionsContainer)
}

#endif //CHRYSALIS_INSTRUCTIONSCONTAINER_H