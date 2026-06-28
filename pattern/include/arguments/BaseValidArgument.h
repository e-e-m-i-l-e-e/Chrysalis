#ifndef CHRYSALIS_BASEVALIDARGUMENT_H
#define CHRYSALIS_BASEVALIDARGUMENT_H

#include <boost/serialization/export.hpp>

#include "BaseArgument.h"

#define VALID_ARGUMENTS ((NumberArgument)(double)) ((NameArgument)(std::string))

namespace Chrysalis {

    #define FORWARD_DECLARE(r, data, pair) class BOOST_PP_SEQ_ELEM(0, pair);
    BOOST_PP_SEQ_FOR_EACH(FORWARD_DECLARE, _, VALID_ARGUMENTS)
    #undef FORWARD_DECLARE

    template<typename T>
    class BaseValidArgument: public BaseArgument<T> {
        SERIALIZE_DERIVED_FROM(BaseArgument<T>)
        #define PROVIDE_SERIALIZATION_ACCESS_FOR_EACH(r, data, pair) PROVIDE_SERIALIZATION_ACCESS(BOOST_PP_SEQ_ELEM(0, pair))
        BOOST_PP_SEQ_FOR_EACH(PROVIDE_SERIALIZATION_ACCESS_FOR_EACH, _, VALID_ARGUMENTS)
        #undef PROVIDE_SERIALIZATION_ACCESS_FOR_EACH
    protected:
        explicit BaseValidArgument(const T& value): value_(value) {}
    public:
        [[nodiscard]] bool isValid() const override {
            return true;
        }
        [[nodiscard]] const T& get() const override {
            return value_;
        }
    private:
        T value_;
    };
}

#define DEFINE_VALID_ARGUMENT(Class, T)                                                                                \
namespace Chrysalis {                                                                                                  \
    class Class: public BaseValidArgument<T> {                                                                         \
    public:                                                                                                            \
        explicit Class(const T& value): BaseValidArgument(value) {}                                                    \
    };                                                                                                                 \
}                                                                                                                      \
BOOST_CLASS_EXPORT_KEY(Chrysalis::Class)

#define DEFINE_VALID_ARGUMENT_FOR_EACH(r, data, pair) DEFINE_VALID_ARGUMENT(BOOST_PP_SEQ_ELEM(0, pair), BOOST_PP_SEQ_ELEM(1, pair))
BOOST_PP_SEQ_FOR_EACH(DEFINE_VALID_ARGUMENT_FOR_EACH, _, VALID_ARGUMENTS)
#undef DEFINE_VALID_ARGUMENT_FOR_EACH
#undef DEFINE_VALID_ARGUMENT

namespace Chrysalis {
#define GENERATE_MEMBER_SERIALIZE(r, data, pair) SIMPLE_SERIALIZE_DERIVED_MEMBERS_R(r, BOOST_PP_SEQ_ELEM(0, pair), BaseValidArgument<BOOST_PP_SEQ_ELEM(1, pair)>, value_)
    BOOST_PP_SEQ_FOR_EACH(GENERATE_MEMBER_SERIALIZE, ~, VALID_ARGUMENTS)
#undef GENERATE_MEMBER_SERIALIZE
}

#undef VALID_ARGUMENTS

#endif //CHRYSALIS_BASEVALIDARGUMENT_H