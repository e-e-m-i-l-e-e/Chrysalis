#ifndef CHRYSALIS_OPTIONALARGUMENT_H
#define CHRYSALIS_OPTIONALARGUMENT_H

#include <boost/serialization/export.hpp>

#include "serialization.h"
#include "arguments/PointArgument.h"

namespace Chrysalis {
    template<typename T>
    class SERIALIZABLE_T(OptionalArgument, T) {
        PROVIDE_SERIALIZATION_ACCESS_T(OptionalArgument)
    public:
        explicit OptionalArgument() = default;
        explicit OptionalArgument(const T* argument): argument_(argument) {}
        ~OptionalArgument() {
            delete argument_;
        }
        bool hasArgument() const {
            return argument_;
        }
        const T* argument() const {
            return argument_;
        }
    private:
        const T* argument_;
    };
    SERIALIZATION_CONSTRUCTOR_T(OptionalArgument, T)
    DEFAULT_SERIALIZE_BASE_MEMBERS_T(OptionalArgument, T, argument_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::OptionalArgument<Chrysalis::PointArgument>)

#endif //CHRYSALIS_OPTIONALARGUMENT_H