#ifndef CHRYSALIS_PATTERNSCONTAINER_H
#define CHRYSALIS_PATTERNSCONTAINER_H

#include "Pattern.h"
#include "BaseContainer.h"

#include "serialization.h"

namespace Chrysalis {
    class SERIALIZABLE(PatternsContainer): public BaseContainer<Pattern> {};
    DEFAULT_SERIALIZE_DERIVED_MEMBERS(PatternsContainer, BaseContainer<Pattern>)
}

#endif //CHRYSALIS_PATTERNSCONTAINER_H