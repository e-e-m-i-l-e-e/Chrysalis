#ifndef CHRYSALIS_RAYARGUMENT_H
#define CHRYSALIS_RAYARGUMENT_H

#include "arguments/LineArgument.h"

/** @defgroup Arguments Arguments
 *  @{
 */
namespace Chrysalis {
    class RayArgument: public LineArgument {
        PROVIDE_SERIALIZATION_ACCESS(RayArgument)
    protected:
        explicit RayArgument(const args::point* origin, const args::point* destination);
    public:
        explicit RayArgument(const args::point* origin, args::number&& angle);

        explicit operator CG::Ray() const;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(RayArgument, LineArgument, origin_, angle_)
    namespace args {
        using ray = RayArgument;
    }
}
/**@}*/

#endif //CHRYSALIS_RAYARGUMENT_H