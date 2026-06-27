#ifndef CHRYSALIS_BASEVALUEARGUMENT_H
#define CHRYSALIS_BASEVALUEARGUMENT_H

#include <boost/optional/optional.hpp>

#include "serialization.h"

namespace Chrysalis {
    template<typename T>
    class SERIALIZABLE_T(BaseValueArgument, T) {
        PROVIDE_SERIALIZATION_ACCESS_T(BaseValueArgument)
    protected:
        explicit BaseValueArgument() = default;
        explicit BaseValueArgument(const T& value): value_(value) {}
    public:
        virtual ~BaseValueArgument() = default;

        virtual bool hasValue() const {
            return value_.has_value();
        }
        virtual T get() const {
            return value_.get();
        }
    private:
        boost::optional<T> value_;
    };
    SIMPLE_SERIALIZE_MEMBERS_T(BaseValueArgument, T, value_)
}

#endif //CHRYSALIS_BASEVALUEARGUMENT_H