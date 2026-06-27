#ifndef CHRYSALIS_POINTARGUMENT_H
#define CHRYSALIS_POINTARGUMENT_H

#include "arguments/BaseArgument.h"
#include "PatternArgument.h"

namespace Chrysalis {
    class SERIALIZABLE(PointArgument) {
        PROVIDE_SERIALIZATION_ACCESS(PointArgument)
    public:
        explicit PointArgument(const name* pointName, const PatternArgument* pattern);
        ~PointArgument();

        bool isValid() const;
        const Point* get() const;
        const std::string& getName() const;
    private:
        /// @uml{composition}
        const name* pointName_;
        /// @uml{composition}
        const PatternArgument* pattern_;
    };
    SIMPLE_SERIALIZE_MEMBERS(PointArgument, pointName_, pattern_)
}

#endif //CHRYSALIS_POINTARGUMENT_H