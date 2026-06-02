#ifndef CHRYSALIS_PARAMETERSCONTAINER_H
#define CHRYSALIS_PARAMETERSCONTAINER_H

#include "Parameter.h"
#include "BaseContainer.h"
#include "serialization.h"

namespace Chrysalis {
    class SERIALIZABLE(ParametersContainer): public BaseContainer<Parameter> {
        PROVIDE_SERIALIZATION_ACCESS(ParametersContainer)
    public:
        void add(Parameter* item) override;
        [[nodiscard]] Parameter* get(const std::string& name) const;
    private:
        std::unordered_map<std::string, Parameter*> parametersMap_;
    };
    DEFAULT_SERIALIZE_MEMBERS(ParametersContainer, parametersMap_)
}

#endif //CHRYSALIS_PARAMETERSCONTAINER_H