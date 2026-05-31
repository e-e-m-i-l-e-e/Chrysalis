#ifndef CHRYSALIS_PARAMETER_H
#define CHRYSALIS_PARAMETER_H

#include <string>
#include <boost/optional/optional.hpp>

#include "serialization.h"
#include "Argument.h"

namespace Chrysalis {
    class SERIALIZABLE(Parameter): public Argument<double> {
        PROVIDE_SERIALIZATION_ACCESS(Parameter)
    public:
        explicit Parameter(std::string name);

        [[nodiscard]] bool isValid() const;
        [[nodiscard]] bool hasAlias() const;
        [[nodiscard]] bool hasValue() const;
        [[nodiscard]] bool hasDefaultValue() const;

        [[nodiscard]] double getValue() const;
        [[nodiscard]] double getDefaultValue() const;
        [[nodiscard]] const std::string& getName() const;
        [[nodiscard]] const std::string& getAlias() const;

        void setName(const std::string& name);
        void setAlias(const std::string& alias);
        void setValue(double value);
        void setDefaultValue(double defaultValue);

    private:
        boost::optional<double> value_;
        boost::optional<double> defaultValue_;

        std::string name_;
        boost::optional<std::string> alias_;
    };
    SERIALIZE_MEMBERS(Parameter, name_, value_, defaultValue_, alias_)
    SERIALIZATION_CONSTRUCTOR(Parameter, name_)
}

#endif //CHRYSALIS_PARAMETER_H