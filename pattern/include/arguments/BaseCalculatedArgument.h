#ifndef CHRYSALIS_BASECACHABLEARGUMENT_H
#define CHRYSALIS_BASECACHABLEARGUMENT_H

#include <boost/optional/optional.hpp>

#include "arguments/BaseArgument.h"

namespace Chrysalis {
    class BaseCalculatedArgument: public BaseArgument<double> {
        SERIALIZE_DERIVED_FROM(BaseArgument, value_)
    protected:
        explicit BaseCalculatedArgument() = default;
        explicit BaseCalculatedArgument(const double& value): value_(value) {}

        virtual double calculate() const = 0;
    public:
        const double& get() const override {
            value_ = calculate();
            return value_.get();
        }
    private:
        mutable boost::optional<double> value_;
    };
}

#endif //CHRYSALIS_BASECACHABLEARGUMENT_H