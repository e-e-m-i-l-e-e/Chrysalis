#ifndef CHRYSALIS_BASEARGUMENT_H
#define CHRYSALIS_BASEARGUMENT_H

#include "CompositiveContainer.h"

namespace Chrysalis {
    template<typename T>
    class BaseArgument {
        SERIALIZED
    protected:
        explicit BaseArgument() = default;
    public:
        virtual ~BaseArgument() = default;

        [[nodiscard]] virtual bool isValid() const = 0;
        [[nodiscard]] virtual const T& get() const = 0;
    };
    namespace args {
        using number = BaseArgument<double>;
        using condition = BaseArgument<bool>;
        template<typename T>
        using container = CompositiveContainer<T>;
    }
}

#endif //CHRYSALIS_BASEARGUMENT_H