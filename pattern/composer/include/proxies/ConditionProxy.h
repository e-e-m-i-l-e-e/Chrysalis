#ifndef CHRYSALIS_CONDITIONPROXY_H
#define CHRYSALIS_CONDITIONPROXY_H

#include "arguments/ConditionalArgument.h"

/** @defgroup Proxy
 * @{
 */
namespace Chrysalis::Proxy {
    struct Condition {
        class Number;
    };
    class Condition::Number {
    public:
        explicit Number(const args::condition* condition, args::number&& number);
        args::number operator>>(double value);
    private:
        const args::condition* condition_;
        args::number number_;
    };
}

#endif //CHRYSALIS_CONDITIONPROXY_H
