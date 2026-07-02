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
        explicit VectorArgument(const args::number* angle, const args::number* length);
        explicit VectorArgument(const args::point* origin, const args::number* angle, const args::number* length);

        ~VectorArgument() override;

        [[nodiscard]] bool isValid() const override;
        [[nodiscard]] const args::number* length() const;

        explicit operator CG::Vector() const;
        explicit operator CG::Segment() const;
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