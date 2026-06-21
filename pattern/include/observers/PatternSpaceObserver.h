#ifndef CHRYSALIS_PATTERNSPACEOBSERVER_H
#define CHRYSALIS_PATTERNSPACEOBSERVER_H

#include "Point.h"

namespace Chrysalis {
    class PatternSpaceObserver {
    protected:
        explicit PatternSpaceObserver() = default;
        virtual ~PatternSpaceObserver() = default;
    public:
        virtual void pointAdded(const Point* point) = 0;
        virtual void relativePointAdded(const Point* from, const Point* to) = 0;
    };
}

#endif //CHRYSALIS_PATTERNSPACEOBSERVER_H