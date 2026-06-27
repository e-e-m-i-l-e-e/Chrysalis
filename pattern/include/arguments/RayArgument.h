#ifndef CHRYSALIS_RAYARGUMENT_H
#define CHRYSALIS_RAYARGUMENT_H

#include "arguments/PointArgument.h"
#include "arguments/BaseArgument.h"

namespace Chrysalis {
    class SERIALIZABLE(RayArgument) {
        PROVIDE_SERIALIZATION_ACCESS(RayArgument)
    protected:
        explicit RayArgument(const PointArgument* origin, const PointArgument* destination);
    public:
        explicit RayArgument(const PointArgument* origin, const num* angle);
        virtual ~RayArgument();

        virtual bool isValid() const;

        double getAngle() const;
        const Point* getOrigin() const;
        const std::string& getOriginName() const;
    protected:
        /// @uml{composition}
        const PointArgument* origin_;
        /// @uml{composition}
        const num* angle_;
    };
    SIMPLE_SERIALIZE_MEMBERS(RayArgument, origin_, angle_)
}

#endif //CHRYSALIS_RAYARGUMENT_H