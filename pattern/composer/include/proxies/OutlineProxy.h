#ifndef CHRYSALIS_OUTLINEPROXY_H
#define CHRYSALIS_OUTLINEPROXY_H

#include <vector>

#include "arguments/PatternPointArgument.h"
#include "instructions/BasePatternInstruction.h"

namespace Chrysalis::Proxy {
    class Outline {
    public:
        class Point;
        explicit Outline(const std::string& name);
        Point operator>>(const PatternPointArgument* point) const;
    private:
        const args::name* name_;
    };
    class Outline::Point {
    public:
        explicit Point(const args::name* name, const PatternPointArgument* point);
        Point& operator>>(const PatternPointArgument* point);
        operator const std::vector<BasePatternInstruction*>&() const;
    private:
        const args::name* name_;
        std::vector<BasePatternInstruction*> instructions_;
    };
}

#endif //CHRYSALIS_OUTLINEPROXY_H
