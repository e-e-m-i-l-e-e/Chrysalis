#ifndef CHRYSALIS_NUMBERARGUMENT_H
#define CHRYSALIS_NUMBERARGUMENT_H

#include "Argument.h"

class NumberArgument: public Argument<double> {
public:
    explicit NumberArgument() = default;
    explicit NumberArgument(const double x) : Argument(x) {};
};

#endif //CHRYSALIS_NUMBERARGUMENT_H