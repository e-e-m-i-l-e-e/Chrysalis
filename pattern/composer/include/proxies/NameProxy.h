#ifndef CHRYSALIS_NAMEPROXY_H
#define CHRYSALIS_NAMEPROXY_H

#include "PointProxy.h"
#include "arguments/VectorArgument.h"
#include "instructions/BasePatternInstruction.h"

namespace Chrysalis::Proxy {
    class Name {
    public:
        class Vector;
        explicit Name(const std::string& name);
        operator const args::name*() const;
        operator const PatternPointArgument*() const;
        Number::Point operator()(const args::number& number) const;
        std::vector<BasePatternInstruction*> operator()(double x, double y) const;
    private:
        const args::name* name_;
    };
    class Name::Vector {
    public:
        class Line;
        explicit Vector(const args::name* name, const args::vector* vector);
        operator std::vector<BasePatternInstruction*>() const;
        Line operator|(const args::line* line) const;
    private:
        const args::name* name_;
        const args::vector* vector_;
    };
    class Name::Vector::Line {
    public:
        explicit Line(const args::name* name, const args::vector* vector, const args::line* line);
        operator std::vector<BasePatternInstruction*>() const;
    private:
        const args::name* name_;
        const args::line* line_;
        const args::vector* vector_;
    };
}

#endif //CHRYSALIS_NAMEPROXY_H
