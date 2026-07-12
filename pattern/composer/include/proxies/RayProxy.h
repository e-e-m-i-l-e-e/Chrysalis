#ifndef CHRYSALIS_RAY_H
#define CHRYSALIS_RAY_H

#include "LineProxy.h"
#include "arguments/RayArgument.h"

#define ray(origin, angle) Proxy::Ray(point(origin), angle)

namespace Chrysalis::Proxy {
    class Ray {
    public:
        explicit Ray(const PatternPointArgument* point, double number);
        Line::Lines::And operator|(const args::container<args::line>* lines_) const;
    private:
        const args::ray* ray_;
    };
}

#endif //CHRYSALIS_RAY_H
