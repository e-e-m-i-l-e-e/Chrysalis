#ifndef CHRYSALIS_NAMEARGUMENT_H
#define CHRYSALIS_NAMEARGUMENT_H

#include "BaseArgument.h"

namespace Chrysalis {
    class NameArgument: public BaseArgument<std::string> {
    public:
        explicit NameArgument() = default;
        explicit NameArgument(const std::string& name): BaseArgument(name) {}
    };
}

#endif //CHRYSALIS_NAMEARGUMENT_H