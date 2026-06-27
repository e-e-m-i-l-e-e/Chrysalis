#ifndef CHRYSALIS_BASEARGUMENT_H
#define CHRYSALIS_BASEARGUMENT_H

#include <string>

#include "serialization.h"

namespace Chrysalis {
    template<typename T>
    class BaseArgument {
        SERIALIZED
    protected:
        explicit BaseArgument() = default;
    public:
        virtual ~BaseArgument() = default;

        virtual bool isValid() const = 0;
        virtual const T& get() const = 0;
    };

    namespace args {
        using number = BaseArgument<double>;
        using name = BaseArgument<std::string>;
    }
}

#endif //CHRYSALIS_BASEARGUMENT_H