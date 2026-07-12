#ifndef CHRYSALIS_LINEPROXY_H
#define CHRYSALIS_LINEPROXY_H

#include <vector>

#include "arguments/LineArgument.h"
#include "instructions/IntersectionPointInstruction.h"

namespace Chrysalis::Proxy {
    class Line {
    public:
        class Lines;
        explicit Line(const args::line* line);
        Lines operator|(const args::container<args::line>* lines) const;
    private:
        const args::line* line_;
    };
    class Line::Lines {
    public:
        class And;
        explicit Lines(const args::line* line, const args::container<args::line>* lines);
        And operator->() const;
    private:
        const args::line* line_;
        const args::container<args::line>* lines_;
    };
    class Line::Lines::And {
    public:
        class Names;
        explicit And(const args::line* line, const args::container<args::line>* lines);
        Names names(const args::container<args::name>* names) const;
        And* operator->();
    private:
        const args::line* line_;
        const args::container<args::line>* lines_;
    };
    class Line::Lines::And::Names {
    public:
        explicit Names(const args::line* line, const args::container<args::line>* lines, const args::container<args::name>* names);
        operator std::vector<BasePatternInstruction*>() const;
    private:
        const args::line* line_;
        const args::container<args::line>* lines_;
        const args::container<args::name>* names_;
    };
}

#endif //CHRYSALIS_LINEPROXY_H
