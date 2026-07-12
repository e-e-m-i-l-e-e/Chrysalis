#ifndef CHRYSALIS_VECTORARGUMENTPROXY_H
#define CHRYSALIS_VECTORARGUMENTPROXY_H

#include <vector>

#include "proxies/NameProxy.h"
#include "proxies/PointProxy.h"
#include "arguments/SegmentArgument.h"

#define up 90
#define right 0
#define left 180
#define down 270

#define angle(from, to) *new VectorFunctionArgument::Angle(point(from), point(to))
#define length(from, to) *new VectorFunctionArgument::Length(point(from), point(to))

#define VECTOR_2(angle, length) Proxy::Vector(angle, length)
#define VECTOR_3(origin, angle, length) Proxy::Vector(point(origin), angle, length)

#define vector(...) BOOST_PP_OVERLOAD(VECTOR_, __VA_ARGS__)(__VA_ARGS__)

namespace Chrysalis::Proxy {
    class Vector {
    public:
        class And {
        public:
            class Vector;
            explicit And(const args::vector* vector);
            Name::Vector name(const args::name* name) const;
            And* operator->();
        private:
            const args::vector* vector_;
        };
        class Segment;

        explicit Vector(const args::point* origin, const args::number& angle, const args::number& length);
        explicit Vector(const args::point* origin, const args::number* angle, double length);
        explicit Vector(const args::point* origin, double angle, const args::number& length);
        explicit Vector(const args::point* origin, double angle, double length);

        explicit Vector(const args::number& angle, const args::number& length);
        explicit Vector(double angle, const args::number& length);
        explicit Vector(double angle, double length);

        operator const args::vector*() const;
        Number::Point::Vector operator<<(Number::Point args) const;

        And operator->() const;
        Point::Vector operator>>(const PatternPointArgument* point) const;
    private:
        args::vector* vector_;
    };
    class Vector::And::Vector {
    public:
        explicit Vector(const args::vector* vector1, const args::vector* vector2);
        operator std::vector<BasePatternInstruction*>() const;
    private:
        const args::vector* vector1_;
        const args::vector* vector2_;
    };
    class Vector::Segment {
    public:
        explicit Segment(const args::vector* vector, const args::segment* segment);
        Number::Vector::Segment operator()(double number) const;
    private:
        const args::vector* vector_;
        const args::segment* segment_;
    };
}

#endif //CHRYSALIS_VECTORARGUMENTPROXY_H
