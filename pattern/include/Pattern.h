#ifndef CHRYSALIS_PATTERN_H
#define CHRYSALIS_PATTERN_H

#include "PatternSpace.h"

namespace Chrysalis {
    class SERIALIZABLE(Pattern) {
        PROVIDE_SERIALIZATION_ACCESS(Pattern)
    public:
        explicit Pattern(const std::string& name, PatternSpace* space);
        ~Pattern();

        const std::string& getName() const;
        const PatternSpace* getSpace() const;
    private:
        std::string name_;
        /// @uml{composition[]}
        PatternSpace* space_;
    };
    SIMPLE_SERIALIZE_MEMBERS(Pattern, name_, space_)
}

#endif //CHRYSALIS_PATTERN_H