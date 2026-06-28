#ifndef CHRYSALIS_PARAMETERSCONTAINER_H
#define CHRYSALIS_PARAMETERSCONTAINER_H

#include "Parameter.h"
#include "BaseNamedInputContainer.h"

namespace Chrysalis {
    class ParametersContainer: public BaseInputContainer<Parameter> {
        SERIALIZE_DERIVED_FROM(BaseInputContainer)
    };
}

#endif //CHRYSALIS_PARAMETERSCONTAINER_H