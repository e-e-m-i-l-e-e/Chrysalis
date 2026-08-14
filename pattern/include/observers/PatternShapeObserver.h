#ifndef CHRYSALIS_OUTLINEOBSERVER_H
#define CHRYSALIS_OUTLINEOBSERVER_H

#include "Outline.h"
#include "BaseObserver.h"

namespace Chrysalis {
    /**
     * @defgroup Observers
     * @{
     */
    class PatternShapeObserver: public BaseObserver<PatternShapeObserver> {
    protected:
        explicit PatternShapeObserver() = default;
    public:
        virtual void pointAdded(const Outline* outline, const Point* point) = 0;
    };
}

#endif //CHRYSALIS_OUTLINEOBSERVER_H
