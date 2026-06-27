#ifndef CHRYSALIS_BASECACHABLEARGUMENT_H
#define CHRYSALIS_BASECACHABLEARGUMENT_H

#include <boost/optional/optional.hpp>

#include "arguments/BaseArgument.h"

namespace Chrysalis {
    template<typename T>
    class BaseCalculatedArgument: public BaseArgument<T> {
        SERIALIZE_DERIVED_FROM(BaseArgument<T>, value_)
    protected:
        explicit BaseCalculatedArgument() = default;
        explicit BaseCalculatedArgument(const T& value): value_(value) {}

        virtual T calculate() const = 0;
    public:
        const T& get() const override {
            value_ = calculate();
            return value_.get();
        }
    private:
        mutable boost::optional<T> value_;
    };
}

#endif //CHRYSALIS_BASECACHABLEARGUMENT_H