#ifndef CHRYSALIS_NUMBERPROXY_H
#define CHRYSALIS_NUMBERPROXY_H

#include "arguments/VectorArgument.h"
#include "arguments/SegmentArgument.h"
#include "arguments/PatternPointArgument.h"
#include "instructions/BasePatternInstruction.h"

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
        explicit Number(const args::number* number);
        operator const args::number*() const;
    private:
        const args::number* number_;
    };
    class Number::Point {
    public:
        class Vector;
        explicit Point(const args::number* number, const PatternPointArgument* point);
        operator const args::number*() const;
        operator const PatternPointArgument*() const;
    private:
        const args::number* number_;
        const PatternPointArgument* point_;
    };
    class Number::Point::Vector {
    public:
        explicit Vector(const args::number* number, const PatternPointArgument* point, const args::vector* vector);
        std::vector<BasePatternInstruction*> operator>>(const args::vector* vector) const;
    private:
        const args::number* number_;
        const args::vector* vector_;
        const PatternPointArgument* point_;
    };
    class Number::Vector::Segment {
    public:
        explicit Segment(const args::number* number, const args::vector* vector, const args::segment* segment);
        operator std::vector<BasePatternInstruction*>() const;
    private:
        const args::number* number_;
        const args::vector* vector_;
        const args::segment* segment_;
    };
    class Number::Segment::And::Segment {
    public:
        explicit Segment(const args::number* number, const args::segment* segment1, const args::segment* segment2);
        operator std::vector<BasePatternInstruction*>() const;
    private:
        const args::number* number_;
        const args::segment* segment1_;
        const args::segment* segment2_;
    };
}

#endif //CHRYSALIS_NUMBERPROXY_H
