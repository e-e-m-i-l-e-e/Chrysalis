#ifndef CHRYSALIS_SEGMENTARGUMENT_H
#define CHRYSALIS_SEGMENTARGUMENT_H

#include "arguments/VectorArgument.h"
#include "arguments/PatternPointArgument.h"

namespace Chrysalis {
    /**
     * @defgroup Arguments
     * @{
     */
    class SegmentArgument: public VectorArgument {
        PROVIDE_SERIALIZATION_ACCESS(SegmentArgument)
    public:
        explicit SegmentArgument(const args::point* origin, const args::point* destination);
        ~SegmentArgument() override;

        const args::point* destination() const;

        explicit operator CG::Segment() const override;
    private:
        /// @uml{composition}
        const args::point* destination_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(SegmentArgument, VectorArgument, origin_, destination_)
    namespace args {
        using segment = SegmentArgument;
    }
}

#endif //CHRYSALIS_SEGMENTARGUMENT_H