#ifndef CHRYSALIS_POINTARGUMENT_H
#define CHRYSALIS_POINTARGUMENT_H

#include "arguments/BaseArgument.h"
#include "arguments/PatternsContainerArgument.h"

namespace Chrysalis {
    class SERIALIZABLE(PointArgument) {
        PROVIDE_SERIALIZATION_ACCESS(PointArgument)
    public:
        explicit PointArgument(const args::name* name, const args::patterns* patterns);
        ~PointArgument();

        [[nodiscard]] bool isValid() const;
        [[nodiscard]]const Point* get() const;
        [[nodiscard]]const std::string& getName() const;
    private:
        /// @uml{composition}
        const args::name* name_;
        /// @uml{composition}
        const args::patterns* patterns_;
    };
    SIMPLE_SERIALIZE_MEMBERS(PointArgument, name_, patterns_)
    namespace args {
        using point = PointArgument;
    }
}

#endif //CHRYSALIS_POINTARGUMENT_H