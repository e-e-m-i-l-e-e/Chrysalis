#ifndef CHRYSALIS_PATTERN_H
#define CHRYSALIS_PATTERN_H

#include "PatternSpace.h"

namespace Chrysalis {
    class Pattern {
        PROVIDE_SERIALIZATION_ACCESS(Pattern)
    public:
        explicit Pattern(const std::string& name, PatternSpace* space);
        ~Pattern();

        static Pattern* create(const std::string& name);

        [[nodiscard]] PatternSpace* getSpace() const;
        [[nodiscard]] const std::string& getName() const;
    private:
        std::string name_;
        /// @uml{composition[]}
        PatternSpace* space_;
    };
    SERIALIZE_CONSTRUCTION(Pattern, name_, space_)
}

#endif //CHRYSALIS_PATTERN_H