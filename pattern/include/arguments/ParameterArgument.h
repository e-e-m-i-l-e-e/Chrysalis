#ifndef CHRYSALIS_PARAMETERARGUMENT_H
#define CHRYSALIS_PARAMETERARGUMENT_H

#include <boost/serialization/export.hpp>

#include "BaseCalculatedArgument.h"
#include "Parameter.h"
#include "ParameterArgument.h"
#include "arguments/BaseArgument.h"

namespace Chrysalis {
    class SERIALIZABLE(ParameterArgument): public BaseCalculatedArgument<double> {
        PROVIDE_SERIALIZATION_ACCESS(ParameterArgument)
    public:
        explicit ParameterArgument(Parameter* parameter);

        bool isValid() const override;
    protected:
        double calculate() const override;
    private:
        Parameter* parameter_;
    };
    SIMPLE_SERIALIZE_DERIVED_MEMBERS(ParameterArgument, BaseCalculatedArgument<double>, parameter_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::ParameterArgument)

#endif //CHRYSALIS_PARAMETERARGUMENT_H