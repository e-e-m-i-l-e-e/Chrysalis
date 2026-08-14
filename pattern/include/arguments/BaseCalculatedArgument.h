#ifndef CHRYSALIS_BASECACHABLEARGUMENT_H
#define CHRYSALIS_BASECACHABLEARGUMENT_H

#include <boost/optional/optional.hpp>

#include "arguments/BaseArgument.h"

namespace Chrysalis {
    /**
     * @defgroup Arguments
     * @{
     */
    template<typename T>
    class BaseCalculatedArgument: public BaseArgument<T> {
        SERIALIZE_DERIVED_FROM(BaseArgument<T>, value_)
    protected:
        explicit BaseCalculatedArgument() = default;
        explicit BaseCalculatedArgument(const T& value): value_(value) {}

        virtual std::expected<T, Error> calculate() const = 0;
    public:
        std::expected<T, Error> get() const override {
            if (!value_.has_value()) {
                std::expected<T, Error> value = calculate();
                return value.transform([&](T t) {
                    value_ = t;
                    return t;
                });
            }
            return value_.get();
        }
    private:
        mutable boost::optional<T> value_;
    };
}

#endif //CHRYSALIS_BASECACHABLEARGUMENT_H