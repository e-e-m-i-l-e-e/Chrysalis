#ifndef CHRYSALIS_RAYARGUMENT_H
#define CHRYSALIS_RAYARGUMENT_H

#include "arguments/PointArgument.h"

namespace Chrysalis {
    class SERIALIZABLE(RayArgument) {
        PROVIDE_SERIALIZATION_ACCESS(RayArgument)
        class AngleArgument;
    protected:
        explicit RayArgument(const PointArgument* origin, const PointArgument* destination);
    public:
        explicit RayArgument(const PointArgument* origin, const args::number* angle);
        virtual ~RayArgument();

        [[nodiscard]] virtual bool isValid() const;

        [[nodiscard]] double getAngle() const;
        [[nodiscard]] const Point* getOrigin() const;
        [[nodiscard]] const std::string& getOriginName() const;
    protected:
        /// @uml{composition}
        const PointArgument* origin_;
        /// @uml{composition}
        const args::number* angle_;
    };
    SIMPLE_SERIALIZE_MEMBERS(RayArgument, origin_, angle_)
}

#endif //CHRYSALIS_RAYARGUMENT_H