#include "proxies/RayProxy.h"

using namespace Chrysalis;

Proxy::Ray::Ray(const PatternPointArgument* point, const double number)
    : ray_(new RayArgument(point, new Argument(number))) {}

Proxy::Line::Lines::And Proxy::Ray::operator|(const args::container<args::line>* lines_) const {
    return Line::Lines::And(ray_, lines_);
}
