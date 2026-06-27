#ifndef CHRYSALIS_LENGTHARGUMENT_H
#define CHRYSALIS_LENGTHARGUMENT_H

#include "PointArgument.h"
#include "BaseCalculatedArgument.h"

namespace Chrysalis {
    class LengthArgument: public BaseCalculatedArgument<double> {
    public:
        explicit LengthArgument(const PointArgument* from, const PointArgument* to);

        bool isValid() const override;
    protected:
        double calculate() const override;
    private:
        const PointArgument* from_;
        const PointArgument* to_;
    };
}

#endif //CHRYSALIS_LENGTHARGUMENT_H