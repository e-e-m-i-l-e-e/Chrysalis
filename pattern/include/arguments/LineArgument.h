#ifndef CHRYSALIS_LINEARGUMENT_H
#define CHRYSALIS_LINEARGUMENT_H

#include "arguments/PointArgument.h"

namespace Chrysalis {
    class LineArgument {
        PROVIDE_SERIALIZATION_ACCESS(LineArgument)
        class AngleArgument;
    protected:
        explicit LineArgument(const PointArgument* origin, const PointArgument* destination);
    public:
        explicit LineArgument(const PointArgument* origin, const args::number* angle);
        virtual ~LineArgument();

        [[nodiscard]] virtual bool isValid() const;

        [[nodiscard]] const args::number* angle() const;
        [[nodiscard]] const args::point* origin() const;

        explicit operator CGAL::Line() const;
    protected:
        /// @uml{composition}
        const PointArgument* origin_;
        /// @uml{composition}
        const args::number* angle_;
    };
    SERIALIZE_CONSTRUCTION(LineArgument, origin_, angle_)
    namespace args {
        using line = LineArgument;
    }
}

#endif //CHRYSALIS_LINEARGUMENT_H