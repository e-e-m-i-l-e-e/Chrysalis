#ifndef CHRYSALIS_PARAMETERARGUMENT_H
#define CHRYSALIS_PARAMETERARGUMENT_H

#include "Parameter.h"
#include "arguments/NumberArgument.h"

namespace Chrysalis {
    class ParameterArgument: public NumberArgument {
    public:
        explicit ParameterArgument(Parameter* parameter);
    private:
        Parameter* parameter_;
    };
}

#endif //CHRYSALIS_PARAMETERARGUMENT_H