#ifndef CHRYSALIS_PARAMETERSCONTAINER_H
#define CHRYSALIS_PARAMETERSCONTAINER_H

#include "Parameter.h"
#include "BaseNamedInputContainer.h"

namespace Chrysalis {
    class SERIALIZABLE(ParametersContainer): public BaseInputContainer<Parameter> {};
    DEFAULT_SERIALIZE_DERIVED_MEMBERS(ParametersContainer, BaseInputContainer<Parameter>)
}

#endif //CHRYSALIS_PARAMETERSCONTAINER_H