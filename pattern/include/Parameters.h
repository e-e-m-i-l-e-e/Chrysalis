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

        [[nodiscard]] unsigned int count() const;
        void addParameter(Parameter* parameter);
        Parameter* getParameter(const std::string& name);
    private:
        std::unordered_map<std::string, Parameter*> parameters_;
    };
    DEFAULT_SERIALIZE_MEMBERS(Parameters, parameters_)
}

#endif //CHRYSALIS_PARAMETERS_H