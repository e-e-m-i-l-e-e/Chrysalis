#ifndef CHRYSALIS_PARAMETERS_H
#define CHRYSALIS_PARAMETERS_H

#include "serialization.h"
#include "Parameter.h"

namespace Chrysalis {
    class SERIALIZABLE(Parameters) {
        PROVIDE_SERIALIZATION_ACCESS(Parameters)
    public:
        ~Parameters();

        Parameter* at(int index);
        [[nodiscard]] int count() const;

        void addParameter(Parameter* parameter);
        [[nodiscard]] Parameter* getParameter(const std::string& name) const;
    private:
        std::list<Parameter*> parameters_;
        std::unordered_map<std::string, Parameter*> parametersMap_;
    };
    DEFAULT_SERIALIZE_MEMBERS(Parameters, parameters_, parametersMap_)
}

#endif //CHRYSALIS_PARAMETERS_H