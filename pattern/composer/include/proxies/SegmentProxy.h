#ifndef CHRYSALIS_SEGMENT_H
#define CHRYSALIS_SEGMENT_H

#include "LineProxy.h"
#include "VectorProxy.h"
#include "arguments/SegmentArgument.h"

/** @defgroup Proxy
 * @{
 */
namespace Chrysalis::Proxy {
    class Segment {
    public:
        class And {
        public:
            class Segment;

            explicit And(const args::segment* segment);

            Vector::Segment vec(const args::vector* vector) const;
            Segment seg(const args::segment* segment) const;

            And* operator->();
        private:
            const args::segment* segment_;
        };
        explicit Segment(args::segment* segment);
        operator args::segment*() const;
        And operator->() const;
        Vector::And::Vector operator&(const args::vector* vector) const;
        Line::Lines operator|(const args::container<args::line>* lines) const;
        Point::Vector operator>>(const PatternPointArgument* point) const;
    private:
        args::segment* segment_;
    };
    class Segment::And::Segment {
    public:
        struct And {
            class Number;
        };
        explicit Segment(const args::segment* segment1, const args::segment* segment2);
        Number::Segment::And::Segment operator()(args::number&& number) const;
    private:
        const args::segment* segment1_;
        const args::segment* segment2_;
    };
}

#endif //CHRYSALIS_SEGMENT_H
