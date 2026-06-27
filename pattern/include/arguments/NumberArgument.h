#ifndef CHRYSALIS_NUMBERARGUMENT_H
#define CHRYSALIS_NUMBERARGUMENT_H

#include "arguments/BaseValueArgument.h"

namespace Chrysalis {
    class SERIALIZABLE(NumberArgument): public BaseValueArgument<double> {
    public:
        explicit NumberArgument() = default;
        explicit NumberArgument(const double x): BaseValueArgument(x) {}
    };
    DEFAULT_SERIALIZE_DERIVED_MEMBERS(NumberArgument, BaseValueArgument<double>)
}

#endif //CHRYSALIS_NUMBERARGUMENT_H