#ifndef CHRYSALIS_SELECTEDPATTERNS_H
#define CHRYSALIS_SELECTEDPATTERNS_H

#include "PatternSpace.h"

namespace Chrysalis {
    class SERIALIZABLE(SelectedPatterns) {
        PROVIDE_SERIALIZATION_ACCESS(SelectedPatterns)
    public:
        [[nodiscard]] std::list<PatternSpace*>::const_iterator begin() const;
        [[nodiscard]] std::list<PatternSpace*>::const_iterator end() const;

        void add(PatternSpace* pattern);
    private:
        std::list<PatternSpace*> patterns_;
    };
    DEFAULT_SERIALIZE_MEMBERS(SelectedPatterns, patterns_)
}

#endif //CHRYSALIS_SELECTEDPATTERNS_H