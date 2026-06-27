#ifndef CHRYSALIS_BASECACHABLEARGUMENT_H
#define CHRYSALIS_BASECACHABLEARGUMENT_H

#include <boost/optional/optional.hpp>
#include <boost/serialization/export.hpp>

#include "BaseArgument.h"
#include "serialization.h"

namespace Chrysalis {
    template<typename T>
    class SERIALIZABLE_T(BaseCalculatedArgument, T): public BaseArgument<T> {
        PROVIDE_SERIALIZATION_ACCESS_T(BaseCalculatedArgument)
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
    SERIALIZATION_CONSTRUCTOR_T(BaseCalculatedArgument, T, value_)
    SERIALIZE_DERIVED_MEMBERS_T(BaseCalculatedArgument, T, BaseArgument, value_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::BaseCalculatedArgument<double>)

#endif //CHRYSALIS_BASECACHABLEARGUMENT_H