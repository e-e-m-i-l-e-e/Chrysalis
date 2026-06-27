#ifndef CHRYSALIS_BASEVALIDARGUMENT_H
#define CHRYSALIS_BASEVALIDARGUMENT_H

#include <boost/serialization/export.hpp>

#include "BaseArgument.h"
#include "serialization.h"

namespace Chrysalis {
    template<typename T>
    class SERIALIZABLE_T(BaseValidArgument, T): public BaseArgument<T> {
        PROVIDE_SERIALIZATION_ACCESS_T(BaseValidArgument)
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
    SERIALIZATION_CONSTRUCTOR_T(BaseValidArgument, T, value_)
    SERIALIZE_DERIVED_MEMBERS_T(BaseValidArgument, T, BaseArgument, value_)

    class NumberArgument: public BaseValidArgument<double> {
    public:
        explicit NumberArgument(): BaseValidArgument<double>(0) {}
        explicit NumberArgument(const double& value): BaseValidArgument(value) {}
    };
    SERIALIZE_DERIVED_MEMBERS(NumberArgument, BaseValidArgument<double>)

    class NameArgument: public BaseValidArgument<std::string> {
    public:
        explicit NameArgument(): BaseValidArgument<std::string>("") {}
        explicit NameArgument(const std::string& value): BaseValidArgument(value) {}
    };
    SERIALIZE_DERIVED_MEMBERS(NameArgument, BaseValidArgument<std::string>)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::NameArgument)
BOOST_CLASS_EXPORT_KEY(Chrysalis::NumberArgument)
BOOST_CLASS_EXPORT_KEY(Chrysalis::BaseValidArgument<std::string>)
BOOST_CLASS_EXPORT_KEY(Chrysalis::BaseValidArgument<double>)

#endif //CHRYSALIS_BASEVALIDARGUMENT_H