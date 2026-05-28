#ifndef FASHIONDESIGNAPPS_ARGUMENT_H
#define FASHIONDESIGNAPPS_ARGUMENT_H

#include "BaseArgument.h"

class Argument: public BaseArgument {
public:
    explicit Argument(double value);

    double getValue() const override;
private:
    double value_;
};

#endif //FASHIONDESIGNAPPS_ARGUMENT_H