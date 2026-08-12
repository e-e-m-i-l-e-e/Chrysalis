#ifndef CHRYSALIS_VECTORARGUMENT_H
#define CHRYSALIS_VECTORARGUMENT_H

#include "arguments/RayArgument.h"
#include "arguments/PatternPointArgument.h"
#include "arguments/BaseArgument.h"

namespace Chrysalis {
    class VectorArgument: public RayArgument {
        PROVIDE_SERIALIZATION_ACCESS(VectorArgument)
    protected:
        explicit VectorArgument(const args::point* origin, const args::point* destination);
    public:
        explicit VectorArgument(args::number&& angle, args::number&& length);
        explicit VectorArgument(const args::point* origin, args::number&& length);
        explicit VectorArgument(const args::point* origin, args::number&& angle, args::number&& length);

        [[nodiscard]] bool isValid() const override;
        [[nodiscard]] const args::number& length() const;

        explicit operator CG::Vector() const;
        explicit virtual operator CG::Segment() const;
    private:
        /// @uml{composition}
        args::number length_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(VectorArgument, RayArgument, origin_, angle_, length_)
    namespace args {
        using vector = VectorArgument;
    }
}

#endif //CHRYSALIS_VECTORARGUMENT_H