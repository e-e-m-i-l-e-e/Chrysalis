#ifndef CHRYSALIS_NUMBERPROXY_H
#define CHRYSALIS_NUMBERPROXY_H

#include "arguments/VectorArgument.h"
#include "arguments/SegmentArgument.h"
#include "arguments/PatternPointArgument.h"
#include "instructions/DartInstruction.h"
#include "instructions/EdgeDartInstruction.h"
#include "instructions/UnfoldEdgeDartInstruction.h"

namespace Chrysalis
{
    class DartInstruction;
}

/** @defgroup Proxy
 * @{
 */
namespace Chrysalis::Proxy {
    class Number {
    public:
        class Point;
        struct Vector {
            class Segment;
        };
        struct Segment {
            struct And {
                class Segment;
            };
        };
        explicit Number(double value);
        explicit Number(args::number&& number);
        operator args::number&&();
    private:
        args::number number_;
    };
    class Number::Point {
    public:
        class Vector;
        explicit Point(args::number&& number, const PatternPointArgument* point);
        operator args::number&&();
        operator const PatternPointArgument*() const;
    private:
        args::number number_;
        const PatternPointArgument* point_;
    };
    class Number::Point::Vector {
    public:
        explicit Vector(args::number&& number, const PatternPointArgument* point, const args::vector* vector);
        DartInstruction* operator>>(const args::vector* vector);
    private:
        args::number number_;
        const args::vector* vector_;
        const PatternPointArgument* point_;
    };
    class Number::Vector::Segment {
    public:
        explicit Segment(args::number&& number, const args::vector* vector, const args::segment* segment);
        operator EdgeDartInstruction*();
    private:
        args::number number_;
        const args::vector* vector_;
        const args::segment* segment_;
    };
    class Number::Segment::And::Segment {
    public:
        explicit Segment(args::number&& number, const args::segment* segment1, const args::segment* segment2);
        operator UnfoldEdgeDartInstruction*();
    private:
        args::number number_;
        const args::segment* segment1_;
        const args::segment* segment2_;
    };
}

#endif //CHRYSALIS_NUMBERPROXY_H
