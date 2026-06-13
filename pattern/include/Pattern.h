#ifndef CHRYSALIS_PATTERN_H
#define CHRYSALIS_PATTERN_H

#include "PatternSpace.h"

namespace Chrysalis {
    class SERIALIZABLE(Pattern) {
        PROVIDE_SERIALIZATION_ACCESS(Pattern)
    public:
        explicit Pattern(const std::string& name, PatternSpace* space);
        ~Pattern();

        [[nodiscard]] PatternSpace* getSpace() const;
        [[nodiscard]] const std::string& getName() const;
    private:
        std::string name_;
        /// @uml{composition[]}
        PatternSpace* space_;
    };
    SIMPLE_SERIALIZE_MEMBERS(Pattern, name_, space_)
}

#endif //CHRYSALIS_PATTERN_H