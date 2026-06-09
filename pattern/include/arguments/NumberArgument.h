#ifndef CHRYSALIS_NUMBERARGUMENT_H
#define CHRYSALIS_NUMBERARGUMENT_H

#include "BaseArgument.h"

namespace Chrysalis {
    class SERIALIZABLE(NumberArgument): public BaseArgument<double> {
    public:
        explicit NumberArgument() = default;
        explicit NumberArgument(const double x): BaseArgument(x) {}
    protected:
        explicit NumberArgument(const boost::optional<double> x): BaseArgument(x) {}
    };
    DEFAULT_SERIALIZE_DERIVED_MEMBERS(NumberArgument, BaseArgument<double>)
}

#endif //CHRYSALIS_NUMBERARGUMENT_H