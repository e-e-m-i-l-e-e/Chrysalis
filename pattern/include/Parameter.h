#ifndef CHRYSALIS_PARAMETER_H
#define CHRYSALIS_PARAMETER_H

#include "BaseNamedElement.h"
#include "NamedElementsContainer.h"
#include "observers/BaseObservable.h"
#include "observers/ParameterObserver.h"

namespace Chrysalis {
    class Parameter: public BaseNamedElement, public BaseObservable<ParameterObserver> {
        PROVIDE_DEFAULT_SERIALIZATION_ACCESS(Parameter)
        SERIALIZE_DERIVED_FROM(BaseNamedElement, value_, defaultValue_)
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
    using ParametersContainer = NamedElementsContainer<Parameter>;
}

#endif //CHRYSALIS_PARAMETER_H