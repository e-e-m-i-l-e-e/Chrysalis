#ifndef CHRYSALIS_BASEARGUMENT_H
#define CHRYSALIS_BASEARGUMENT_H

#include <string>
#include "serialization.h"

namespace Chrysalis {
    template<typename T>
    class SERIALIZABLE_T(BaseArgument, T) {
    protected:
        explicit BaseArgument() = default;
    public:
        virtual ~BaseArgument() = default;

        virtual bool isValid() const = 0;
        virtual const T& get() const = 0;
    };
    DEFAULT_SERIALIZE_BASE_MEMBERS_T(BaseArgument, T)

    using num = BaseArgument<double>;
    using name = BaseArgument<std::string>;
}

#endif //CHRYSALIS_BASEARGUMENT_H