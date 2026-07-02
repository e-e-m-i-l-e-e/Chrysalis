#include "arguments/OriginPointArgument.h"

using namespace Chrysalis;

const Point* OriginPointArgument::get() const {
    static const Point point(0, 0);
    return &point;
}

const args::name* OriginPointArgument::name() const {
    static const args::name name("O");
    return &name;
}

BasePointArgument* OriginPointArgument::clone() const {
    return new OriginPointArgument(*this);
}
