#ifndef CHRYSALIS_PARAMETERARGUMENT_H
#define CHRYSALIS_PARAMETERARGUMENT_H

#include <boost/serialization/export.hpp>

#include "Parameter.h"
#include "BaseCalculatedArgument.h"

namespace Chrysalis {
    class ParameterArgument: public BaseCalculatedArgument {
        PROVIDE_SERIALIZATION_ACCESS(ParameterArgument)
    public:
        explicit ParameterArgument(Parameter* parameter);

        bool isValid() const override;
    protected:
        double calculate() const override;
    private:
        Parameter* parameter_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(ParameterArgument, BaseCalculatedArgument, parameter_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::ParameterArgument)

#endif //CHRYSALIS_PARAMETERARGUMENT_H