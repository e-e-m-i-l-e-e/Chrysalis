#ifndef CHRYSALIS_SEGMENT_H
#define CHRYSALIS_SEGMENT_H

#include "LineProxy.h"
#include "VectorProxy.h"
#include "arguments/SegmentArgument.h"

#define REPEAT_SEGMENT(d, data, elem) segment elem
#define segments(...) new args::container(std::initializer_list<args::line*>{                                          \
    BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TRANSFORM(REPEAT_SEGMENT, ~, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)))                \
})
#define segment(from, to) Proxy::Segment(new args::segment(point(from), point(to)))

#define DART_2(from, to) seg(segment(from, to))
#define DART_3(origin, angle, length) vec(vector(origin, angle, length))

#define dart(...) BOOST_PP_OVERLOAD(DART_, __VA_ARGS__)(__VA_ARGS__)
#define edge(from, to) Proxy::Segment(segment(from, to))

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
        Number::Segment::And::Segment operator()(const args::number& number) const;
    private:
        const args::segment* segment1_;
        const args::segment* segment2_;
    };
}

#endif //CHRYSALIS_SEGMENT_H
