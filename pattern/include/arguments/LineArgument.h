#ifndef CHRYSALIS_LINEARGUMENT_H
#define CHRYSALIS_LINEARGUMENT_H

#include "arguments/PatternPointArgument.h"

namespace Chrysalis {
    class LineArgument {
        PROVIDE_SERIALIZATION_ACCESS(LineArgument)
    protected:
        explicit LineArgument(const args::point* origin, const args::point* destination);
    public:
        explicit LineArgument(const args::point* origin, const args::number* angle);
        virtual ~LineArgument();

        [[nodiscard]] virtual bool isValid() const;

        [[nodiscard]] const args::number* angle() const;
        [[nodiscard]] const args::point* origin() const;

        explicit operator CG::Line() const;
    protected:
        /// @uml{composition}
        const args::point* origin_;
        /// @uml{composition}
        const args::number* angle_;
    };
    SERIALIZE_CONSTRUCTION(LineArgument, origin_, angle_)
    namespace args {
        using line = LineArgument;
    }
}

#endif //CHRYSALIS_LINEARGUMENT_H