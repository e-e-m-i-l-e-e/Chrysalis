#ifndef CHRYSALIS_PARAMETERARGUMENT_H
#define CHRYSALIS_PARAMETERARGUMENT_H

#include <boost/serialization/export.hpp>

#include "Parameter.h"
#include "BaseCalculatedArgument.h"

/** @defgroup Arguments Arguments
 *  @{
 */
namespace Chrysalis {
    class ParameterArgument: public BaseCalculatedArgument<double> {
        PROVIDE_SERIALIZATION_ACCESS(ParameterArgument)
    public:
        explicit ParameterArgument(Parameter* parameter);
    protected:
        std::expected<double, Error> calculate() const override;
    private:
        Parameter* parameter_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(ParameterArgument, BaseCalculatedArgument<double>, parameter_)
}
/**@}*/

#endif //CHRYSALIS_PARAMETERARGUMENT_H