#ifndef CHRYSALIS_OPTIONALARGUMENT_H
#define CHRYSALIS_OPTIONALARGUMENT_H

#include "serialization.h"

namespace Chrysalis {
    template<typename T>
    class OptionalArgument {
        SERIALIZE(argument_)
    public:
        explicit OptionalArgument() = default;
        explicit OptionalArgument(const T* argument): argument_(argument) {}
        ~OptionalArgument() {
            delete argument_;
        }
        [[nodiscard]] bool hasArgument() const {
            return argument_;
        }
        const T* argument() const {
            return argument_;
        }
    private:
        const T* argument_;
    };
    namespace args {
        template<typename T>
        using optional = OptionalArgument<T>;
    }
}

#endif //CHRYSALIS_OPTIONALARGUMENT_H