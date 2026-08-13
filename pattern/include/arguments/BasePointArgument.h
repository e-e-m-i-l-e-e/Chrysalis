#ifndef CHRYSALIS_BASEPOINTARGUMENT_H
#define CHRYSALIS_BASEPOINTARGUMENT_H

#include "Point.h"
#include "arguments/Argument.h"

namespace Chrysalis {
    class BasePointArgument {
        SERIALIZED
    protected:
        explicit BasePointArgument() = default;
    public:
        virtual ~BasePointArgument() = default;

        [[nodiscard]] virtual bool isValid() const;
        [[nodiscard]] virtual const Point* get() const = 0;
        [[nodiscard]] virtual const args::name& name() const = 0;
        [[nodiscard]] virtual BasePointArgument* clone() const = 0;

        [[nodiscard]] virtual operator CG::Point() const;
    };
    namespace args {
        using point = BasePointArgument;
    }
}

#endif //CHRYSALIS_BASEPOINTARGUMENT_H