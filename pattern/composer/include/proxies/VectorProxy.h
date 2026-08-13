#ifndef CHRYSALIS_VECTORARGUMENTPROXY_H
#define CHRYSALIS_VECTORARGUMENTPROXY_H

#include <vector>

#include "proxies/NameProxy.h"
#include "proxies/PointProxy.h"
#include "arguments/SegmentArgument.h"

namespace Chrysalis::Proxy {
    class Vector {
    public:
        class And {
        public:
            class Vector;
            explicit And(const args::vector* vector);
            Name::Vector name(args::name&& name) const;
            And* operator->();
        private:
            const args::vector* vector_;
        };
        class Segment;

        explicit Vector(const args::point* origin, args::number&& angle, args::number&& length);
        explicit Vector(const args::point* origin, args::number&& angle, double length);
        explicit Vector(const args::point* origin, double angle, args::number&& length);
        explicit Vector(const args::point* origin, double angle, double length);

        explicit Vector(args::number&& angle, args::number&& length);
        explicit Vector(double angle, args::number&& length);
        explicit Vector(double angle, double length);

        operator const args::vector*() const;
        Number::Point::Vector operator<<(Number::Point&& args) const;

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
