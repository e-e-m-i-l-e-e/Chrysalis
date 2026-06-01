#ifndef CHRYSALIS_ACTIVEPATTERNS_H
#define CHRYSALIS_ACTIVEPATTERNS_H

#include "PatternSpace.h"

namespace Chrysalis {
    class SelectedPatterns {
    public:
        std::list<PatternSpace*>::const_iterator begin() const;
        std::list<PatternSpace*>::const_iterator end() const;
    private:
        std::list<PatternSpace*> patterns_;
    };
}

#endif //CHRYSALIS_ACTIVEPATTERNS_H