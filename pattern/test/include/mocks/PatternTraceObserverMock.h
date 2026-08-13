#ifndef CHRYSALIS_PATTERNSPACEOBSERVERMOCK_H
#define CHRYSALIS_PATTERNSPACEOBSERVERMOCK_H

#include <gmock/gmock.h>

#include "observers/PatternTraceObserver.h"

namespace Chrysalis {
    class PatternTraceObserverMock: public PatternTraceObserver {
    public:
        MOCK_METHOD(void, pointAdded, (const Point* point), (override));
        MOCK_METHOD(void, curveAdded, (const Curve* curve), (override));
        MOCK_METHOD(void, transformed, (const Transformation& transformation), (override));
        MOCK_METHOD(void, relativePointConnectionAdded, (const Point* from, const Point* to), (override));
        MOCK_METHOD(void, relativePointConnectionRemoved, (const Point* from, const Point* to), (override));
    };
}

#endif //CHRYSALIS_PATTERNSPACEOBSERVERMOCK_H
