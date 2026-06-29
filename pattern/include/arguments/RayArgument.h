#ifndef CHRYSALIS_RAYARGUMENT_H
#define CHRYSALIS_RAYARGUMENT_H

#include "arguments/LineArgument.h"

namespace Chrysalis {
    class RayArgument: public LineArgument {
        PROVIDE_SERIALIZATION_ACCESS(RayArgument)
    protected:
        explicit RayArgument(const PointArgument* origin, const PointArgument* destination);
    public:
        explicit RayArgument(const PointArgument* origin, const args::number* angle);

        explicit operator CG::Ray() const;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(RayArgument, LineArgument, origin_, angle_)
    namespace args {
        using ray = RayArgument;
    }
}

#endif //CHRYSALIS_RAYARGUMENT_H