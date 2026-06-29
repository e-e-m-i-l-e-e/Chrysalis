#ifndef CHRYSALIS_VECTORARGUMENT_H
#define CHRYSALIS_VECTORARGUMENT_H

#include "arguments/RayArgument.h"
#include "arguments/PointArgument.h"
#include "arguments/BaseArgument.h"

namespace Chrysalis {
    class VectorArgument: public RayArgument {
        PROVIDE_SERIALIZATION_ACCESS(VectorArgument)
        class LengthArgument;
    protected:
        explicit VectorArgument(const PointArgument* origin, const PointArgument* destination);
    public:
        explicit VectorArgument(const PointArgument* origin, const args::number* angle, const args::number* length);

        ~VectorArgument() override;

        [[nodiscard]] double getLength() const;
        [[nodiscard]] bool isValid() const override;

        explicit operator CGAL::Vector() const;
        explicit operator CGAL::Segment() const;
    private:
        /// @uml{composition}
        const args::number* length_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(VectorArgument, RayArgument, origin_, angle_, length_)
    namespace args {
        using vector = VectorArgument;
    }
}

#endif //CHRYSALIS_VECTORARGUMENT_H