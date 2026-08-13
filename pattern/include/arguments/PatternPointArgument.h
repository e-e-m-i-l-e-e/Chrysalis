#ifndef CHRYSALIS_POINTARGUMENT_H
#define CHRYSALIS_POINTARGUMENT_H

#include "CGAL.h"
#include "arguments/Argument.h"
#include "arguments/BasePointArgument.h"
#include "arguments/PatternsContainerArgument.h"

namespace Chrysalis {
    class PatternPointArgument: public BasePointArgument {
        PROVIDE_SERIALIZATION_ACCESS(PatternPointArgument)
    public:
        explicit PatternPointArgument(args::name&& name, const args::patterns* patterns);
        PatternPointArgument(const PatternPointArgument& other);
        ~PatternPointArgument() override;

        [[nodiscard]] bool isValid() const override;
        [[nodiscard]] const Point* get() const override;
        [[nodiscard]] const args::name& name() const override;
        [[nodiscard]] BasePointArgument* clone() const override;

        [[nodiscard]] operator CG::Point() const override;
    private:
        /// @uml{composition}
        args::name name_;
        /// @uml{composition}
        const args::patterns* patterns_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(PatternPointArgument, BasePointArgument, name_, patterns_)
}

#endif //CHRYSALIS_POINTARGUMENT_H