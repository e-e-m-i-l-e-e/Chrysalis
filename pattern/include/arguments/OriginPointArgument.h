#ifndef CHRYSALIS_ORIGINPOINTARGUMENT_H
#define CHRYSALIS_ORIGINPOINTARGUMENT_H

#include "arguments/BasePointArgument.h"

namespace Chrysalis {
    class OriginPointArgument: public BasePointArgument {
        SERIALIZE_DERIVED_FROM(BasePointArgument)
    public:
        [[nodiscard]] const Point* get() const override;
        [[nodiscard]] const args::name* name() const override;
        [[nodiscard]] BasePointArgument* clone() const override;
    };
    namespace args {
        using origin = OriginPointArgument;
    }
}

#endif //CHRYSALIS_ORIGINPOINTARGUMENT_H