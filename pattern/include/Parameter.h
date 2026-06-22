#ifndef CHRYSALIS_PARAMETER_H
#define CHRYSALIS_PARAMETER_H

#include "BaseNamedInput.h"
#include "observers/BaseObservable.h"
#include "observers/ParameterObserver.h"

namespace Chrysalis {
    class SERIALIZABLE(Parameter): public BaseNamedInput, public BaseObservable<ParameterObserver> {
        PROVIDE_DEFAULT_SERIALIZATION_ACCESS(Parameter)
    public:
        explicit Parameter(const std::string& name);

        static Parameter* create(const std::string& name, double value);
        static Parameter* createDefault(const std::string& name, double defaultValue);

        [[nodiscard]] bool isValid() const;
        [[nodiscard]] bool hasValue() const;
        [[nodiscard]] bool hasDefaultValue() const;

        [[nodiscard]] double getValue() const;
        [[nodiscard]] double getDefaultValue() const;

        void setValue(double value);
        void setDefaultValue(double defaultValue);
    private:
        boost::optional<double> value_;
        boost::optional<double> defaultValue_;
    };
    DEFAULT_SERIALIZE_DERIVED_MEMBERS(Parameter, BaseNamedInput, value_, defaultValue_)
}

#endif //CHRYSALIS_PARAMETER_H