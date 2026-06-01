#ifndef CHRYSALIS_PATTERNSCONTAINER_H
#define CHRYSALIS_PATTERNSCONTAINER_H

#include "Pattern.h"
#include "BaseContainer.h"

#include "serialization.h"

namespace Chrysalis {
    class SERIALIZABLE(PatternsContainer): public BaseContainer<Pattern> {};
    DEFAULT_SERIALIZE_MEMBERS(PatternsContainer)
}

#endif //CHRYSALIS_PATTERNSCONTAINER_H