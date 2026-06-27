#ifndef CHRYSALIS_VECTORARGUMENT_H
#define CHRYSALIS_VECTORARGUMENT_H

#include "VectorArgument.h"
#include "arguments/RayArgument.h"
#include "arguments/PointArgument.h"
#include "arguments/BaseArgument.h"

namespace Chrysalis {
    class SERIALIZABLE(VectorArgument): public RayArgument {
        PROVIDE_SERIALIZATION_ACCESS(VectorArgument)
    protected:
        explicit VectorArgument(const PointArgument* origin, const PointArgument* destination);
    public:
        explicit VectorArgument(const PointArgument* origin, const num* angle, const num* length);

        ~VectorArgument() override;

        bool isValid() const override;

        double getLength() const;
    private:
        /// @uml{composition}
        const num* length_;
    };
    SIMPLE_SERIALIZE_DERIVED_MEMBERS(VectorArgument, RayArgument, origin_, angle_, length_)
}

#endif //CHRYSALIS_VECTORARGUMENT_H