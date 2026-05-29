#ifndef CHRYSALIS_PARAMETER_H
#define CHRYSALIS_PARAMETER_H

#include <string>

#include "serialization.h"
#include "BaseArgument.h"

namespace Chrysalis {
    class SERIALIZABLE(Parameter): public BaseArgument {
        PROVIDE_SERIALIZATION_ACCESS(Parameter)
    public:
        explicit Parameter(const std::string& name, double value);

        [[nodiscard]] double getValue() const override;
        void setValue(double value);

        [[nodiscard]] const std::string& getName() const;
    private:
        double value_;
        std::string name_;
    };
    SIMPLE_SERIALIZE_MEMBERS(Parameter, name_, value_)
}

#endif //CHRYSALIS_PARAMETER_H