#ifndef CHRYSALIS_PATTERNTRACEOBSERVER_H
#define CHRYSALIS_PATTERNTRACEOBSERVER_H

#include "Point.h"
#include "Curve.h"
#include "Transformation.h"

namespace Chrysalis {
    class PatternTraceObserver {
    protected:
        explicit PatternTraceObserver() = default;
        virtual ~PatternTraceObserver() = default;
    public:
        virtual void pointAdded(const Point* point) = 0;
        virtual void curveAdded(const Curve* curve) = 0;
        virtual void transformed(const Transformation& transformation) = 0;
        virtual void relativePointConnectionAdded(const Point* from, const Point* to) = 0;
        virtual void relativePointConnectionRemoved(const Point* from, const Point* to) = 0;
    };
}

#endif //CHRYSALIS_PATTERNTRACEOBSERVER_H