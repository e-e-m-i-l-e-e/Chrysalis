#ifndef CHRYSALIS_BASEVALIDARGUMENT_H
#define CHRYSALIS_BASEVALIDARGUMENT_H

#include <boost/serialization/export.hpp>

#include "BaseArgument.h"

#define VALID_ARGUMENTS ((Number)(double)) ((Name)(std::string))

#define CLASS(argument) BOOST_PP_CAT(BOOST_PP_SEQ_ELEM(0, argument), Argument)
#define TYPE(argument) BOOST_PP_SEQ_ELEM(1, argument)

namespace Chrysalis {
#define FORWARD_DECLARE(r, data, argument) class CLASS(argument);
    BOOST_PP_SEQ_FOR_EACH(FORWARD_DECLARE, _, VALID_ARGUMENTS)
#undef FORWARD_DECLARE

    template<typename T>
    class BaseValidArgument : public BaseArgument<T> {
        SERIALIZE_DERIVED_FROM(BaseArgument<T>)

#define PROVIDE_SERIALIZATION_ACCESS_FOR_EACH(r, data, argument) PROVIDE_SERIALIZATION_ACCESS(CLASS(argument))
        BOOST_PP_SEQ_FOR_EACH(PROVIDE_SERIALIZATION_ACCESS_FOR_EACH, _, VALID_ARGUMENTS)
#undef PROVIDE_SERIALIZATION_ACCESS_FOR_EACH

    protected:
        explicit BaseValidArgument(const T& value) : value_(value) {}
    public:
        [[nodiscard]] bool isValid() const override { return true; }
        [[nodiscard]] const T& get() const override { return value_; }
    private:
        T value_;
    };
}

#define DEFINE_VALID_ARGUMENT(r, data, argument)                                                                       \
namespace Chrysalis {                                                                                                  \
    class CLASS(argument) : public BaseValidArgument<TYPE(argument)> {                                                 \
    public:                                                                                                            \
        explicit CLASS(argument)(const TYPE(argument)& value): BaseValidArgument<TYPE(argument)>(value) {}             \
    };                                                                                                                 \
    SIMPLE_SERIALIZE_DERIVED_MEMBERS_R(r, CLASS(argument), BaseValidArgument<TYPE(argument)>, value_)                  \
}                                                                                                                      \
BOOST_CLASS_EXPORT_KEY(Chrysalis::CLASS(argument))
BOOST_PP_SEQ_FOR_EACH(DEFINE_VALID_ARGUMENT, _, VALID_ARGUMENTS)
#undef DEFINE_VALID_ARGUMENT

#undef TYPE
#undef CLASS
#undef VALID_ARGUMENTS

#endif // CHRYSALIS_BASEVALIDARGUMENT_H