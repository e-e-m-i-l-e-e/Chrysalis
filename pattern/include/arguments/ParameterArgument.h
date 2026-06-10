#ifndef CHRYSALIS_PARAMETERARGUMENT_H
#define CHRYSALIS_PARAMETERARGUMENT_H

#include <boost/serialization/export.hpp>

#include "Parameter.h"
#include "BaseObserver.h"
#include "ParameterArgument.h"
#include "arguments/NumberArgument.h"

namespace Chrysalis {
    class SERIALIZABLE(ParameterArgument): public NumberArgument, public BaseObserver {
        PROVIDE_SERIALIZATION_ACCESS(ParameterArgument)
    public:
        explicit ParameterArgument(Parameter* parameter);

        void valueChanged() override;
    private:
        Parameter* parameter_;
    };
    SIMPLE_SERIALIZE_DERIVED_MEMBERS(ParameterArgument, NumberArgument, parameter_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::ParameterArgument)

#endif //CHRYSALIS_PARAMETERARGUMENT_H