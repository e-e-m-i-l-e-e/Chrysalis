#ifndef CHRYSALIS_CONDITIONPROXY_H
#define CHRYSALIS_CONDITIONPROXY_H

#include "arguments/ConditionalArgument.h"

namespace Chrysalis::Proxy {
    struct Condition {
        class Number;
    };
    class Condition::Number {
    public:
        explicit Number(const args::condition* condition, const args::number* number);
        const args::conditional& operator>>(double value) const;
    private:
        const args::condition* condition_;
        const args::number* number_;
    };
}

#endif //CHRYSALIS_CONDITIONPROXY_H
