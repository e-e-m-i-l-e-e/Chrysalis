#ifndef CHRYSALIS_BASEVALIDARGUMENT_H
#define CHRYSALIS_BASEVALIDARGUMENT_H

#include <boost/serialization/export.hpp>

#include "BaseArgument.h"
#include "BaseValidArgument.h"

namespace Chrysalis {
    class NameArgument;
    class NumberArgument;

    template<typename T>
    class SERIALIZABLE_T(BaseValidArgument): public BaseArgument<T> {
        PROVIDE_SERIALIZATION_ACCESS_T(BaseValidArgument)
        // SERIALIZE_DERIVED_FROM(BaseArgument<T>)
        // PROVIDE_SERIALIZATION_ACCESS(NameArgument)
        // PROVIDE_SERIALIZATION_ACCESS(NumberArgument)
    protected:
        explicit BaseValidArgument(const T& value): value_(value) {}
    public:
        bool isValid() const override {
            return true;
        }
        const T& get() const override {
            return value_;
        }
    private:
        T value_;
    };
    SERIALIZE_DERIVED_T(BaseValidArgument, BaseArgument, value_)

    class NumberArgument: public BaseValidArgument<double> {
    public:
        explicit NumberArgument(): BaseValidArgument<double>(0) {}
        explicit NumberArgument(const double& value): BaseValidArgument(value) {}
    };
    SERIALIZE_DERIVED_MEMBERS(NumberArgument, BaseValidArgument<double>)
    // SIMPLE_SERIALIZE_DERIVED_MEMBERS(NumberArgument, BaseValidArgument<double>, value_)

    class NameArgument: public BaseValidArgument<std::string> {
    public:
        explicit NameArgument(): BaseValidArgument<std::string>("") {}
        explicit NameArgument(const std::string& value): BaseValidArgument(value) {}
    };
    SERIALIZE_DERIVED_MEMBERS(NameArgument, BaseValidArgument<std::string>)
    // SIMPLE_SERIALIZE_DERIVED_MEMBERS(NameArgument, BaseValidArgument<std::string>, value_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::NameArgument)
BOOST_CLASS_EXPORT_KEY(Chrysalis::NumberArgument)

#endif //CHRYSALIS_BASEVALIDARGUMENT_H