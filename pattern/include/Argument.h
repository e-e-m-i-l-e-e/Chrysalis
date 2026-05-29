#ifndef CHRYSALIS_ARGUMENT_H
#define CHRYSALIS_ARGUMENT_H

#include "BaseArgument.h"

class Argument: public BaseArgument {
public:
    explicit Argument(double value);

    double getValue() const override;
private:
    double value_;
};

#endif //CHRYSALIS_ARGUMENT_H