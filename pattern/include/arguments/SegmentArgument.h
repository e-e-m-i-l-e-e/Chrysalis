#ifndef CHRYSALIS_SEGMENTARGUMENT_H
#define CHRYSALIS_SEGMENTARGUMENT_H

#include "arguments/PointArgument.h"
#include "arguments/VectorArgument.h"

namespace Chrysalis {
    class SegmentArgument: public VectorArgument {
    public:
        explicit SegmentArgument(const PointArgument* pointFrom, const PointArgument* pointTo);
        ~SegmentArgument() override;
    private:
        /// @uml{composition}
        const PointArgument* pointFrom_;
        /// @uml{composition}
        const PointArgument* pointTo_;
    };
}

#endif //CHRYSALIS_SEGMENTARGUMENT_H