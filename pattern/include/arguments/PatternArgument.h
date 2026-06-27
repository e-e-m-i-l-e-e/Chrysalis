#ifndef CHRYSALIS_PATTERNARGUMENT_H
#define CHRYSALIS_PATTERNARGUMENT_H

#include <boost/serialization/export.hpp>

#include "PatternSpace.h"
#include "arguments/BaseValidArgument.h"

namespace Chrysalis {
    class PatternArgument: public BaseValidArgument<PatternSpace*> {
    public:
        explicit PatternArgument(): BaseValidArgument<Chrysalis::PatternSpace*>(nullptr) {}
        explicit PatternArgument(PatternSpace* pattern): BaseValidArgument(pattern) {}
    };
    SERIALIZE_DERIVED_MEMBERS(PatternArgument, BaseValidArgument<PatternSpace*>)
}

// BOOST_CLASS_EXPORT(Chrysalis::BaseValidArgument<Chrysalis::PatternSpace*>)
// BOOST_CLASS_EXPORT(Chrysalis::PatternArgument)

#endif //CHRYSALIS_PATTERNARGUMENT_H
