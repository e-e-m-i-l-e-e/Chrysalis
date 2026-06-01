#ifndef CHRYSALIS_NUMBERARGUMENT_H
#define CHRYSALIS_NUMBERARGUMENT_H

#include "BaseArgument.h"

namespace Chrysalis {
    class NumberArgument: public BaseArgument<double> {
    public:
        explicit NumberArgument() = default;
        explicit NumberArgument(const double x): BaseArgument(x) {};
    };
}

#endif //CHRYSALIS_NUMBERARGUMENT_H