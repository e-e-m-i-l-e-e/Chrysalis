#ifndef CHRYSALIS_INSTRUCTIONSCONTAINER_H
#define CHRYSALIS_INSTRUCTIONSCONTAINER_H

#include <boost/optional/optional.hpp>

#include "serialization.h"

#include "BaseContainer.h"
#include "PatternInstructionsContainer.h"

namespace Chrysalis {
    class SERIALIZABLE(InstructionsContainer): public BaseContainer<PatternInstructionsContainer> {
    public:
        void execute();
    private:
        boost::optional<std::list<PatternInstructionsContainer*>::const_iterator> nextInstruction_;
    };
    DEFAULT_SERIALIZE_MEMBERS(InstructionsContainer)
}

#endif //CHRYSALIS_INSTRUCTIONSCONTAINER_H