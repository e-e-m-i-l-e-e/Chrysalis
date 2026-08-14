#ifndef CHRYSALIS_PROXYPOINT_H
#define CHRYSALIS_PROXYPOINT_H

#include "instructions/MovePointInstruction.h"
#include "proxies/NumberProxy.h"

/** @defgroup Proxy
 * @{
 */
namespace Chrysalis::Proxy {
    class Point {
    public:
        class Number;
        class Vector;
        explicit Point(const PatternPointArgument* point);
        operator const PatternPointArgument*() const;
        Proxy::Number operator()(args::number&& number) const;
    private:
        const PatternPointArgument* point_;
    };
    class Point::Vector {
    public:
        struct And {
            class Vector;
        };
        explicit Vector(const PatternPointArgument* point, const args::vector* vector);
        operator MovePointInstruction*() const;
        And::Vector operator<<(const args::vector* vector) const;
    private:
        const args::vector* vector_;
        const PatternPointArgument* point_;
    };
    class Point::Vector::And::Vector {
    public:
        explicit Vector(const PatternPointArgument* point, const args::vector* vector1, const args::vector* vector2);
        operator MovePointInstruction*() const;
    private:
        const PatternPointArgument* point_;
        const args::vector* vector1_;
        const args::vector* vector2_;
    };
}

#endif //CHRYSALIS_PROXYPOINT_H
