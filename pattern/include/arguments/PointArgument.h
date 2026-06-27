#ifndef CHRYSALIS_POINTARGUMENT_H
#define CHRYSALIS_POINTARGUMENT_H

#include "NameArgument.h"
#include "PatternArgument.h"

namespace Chrysalis {
    class SERIALIZABLE(PointArgument) {
        PROVIDE_SERIALIZATION_ACCESS(PointArgument)
    public:
        explicit PointArgument(const NameArgument* name, const PatternArgument* pattern);
        ~PointArgument();

        bool isValid() const;
        const Point* get() const;
        const std::string& getName() const;
    private:
        /// @uml{composition}
        const NameArgument* name_;
        /// @uml{composition}
        const PatternArgument* pattern_;
    };
    SIMPLE_SERIALIZE_MEMBERS(PointArgument, name_, pattern_)
}

#endif //CHRYSALIS_POINTARGUMENT_H