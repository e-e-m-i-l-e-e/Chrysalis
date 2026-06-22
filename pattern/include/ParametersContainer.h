#ifndef CHRYSALIS_PARAMETERSCONTAINER_H
#define CHRYSALIS_PARAMETERSCONTAINER_H

#include "Parameter.h"
#include "BaseContainer.h"
#include "BaseInputContainer.h"
#include "serialization.h"

namespace Chrysalis {
    class SERIALIZABLE(ParametersContainer): public BaseInputContainer<Parameter> {
    public:
        void add(Parameter* item) override;
    };
    DEFAULT_SERIALIZE_DERIVED_MEMBERS(ParametersContainer, BaseInputContainer<Parameter>)
}

#endif //CHRYSALIS_PARAMETERSCONTAINER_H