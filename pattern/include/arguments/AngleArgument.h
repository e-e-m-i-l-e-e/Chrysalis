#ifndef CHRYSALIS_ANGLEARGUMENT_H
#define CHRYSALIS_ANGLEARGUMENT_H

#include "BaseCalculatedArgument.h"
#include "PointArgument.h"

namespace Chrysalis {
    class AngleArgument: public BaseCalculatedArgument<double> {
    public:
        explicit AngleArgument(const PointArgument* from, const PointArgument* to);

        bool isValid() const override;
    protected:
        double calculate() const override;
    private:
        const PointArgument* from_;
        const PointArgument* to_;
    };
}

#endif //CHRYSALIS_ANGLEARGUMENT_H