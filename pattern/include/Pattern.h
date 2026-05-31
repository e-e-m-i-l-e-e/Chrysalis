#ifndef CHRYSALIS_PATTERN_H
#define CHRYSALIS_PATTERN_H

#include "PatternSpace.h"

namespace Chrysalis {
    class Pattern {
    public:
        explicit Pattern(const std::string& name, PatternSpace* space);
        ~Pattern();
    private:
        std::string name_;
        /// @uml{composition[]}
        PatternSpace* space_;
    };
}

#endif //CHRYSALIS_PATTERN_H