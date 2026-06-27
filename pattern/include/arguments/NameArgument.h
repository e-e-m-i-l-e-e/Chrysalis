#ifndef CHRYSALIS_NAMEARGUMENT_H
#define CHRYSALIS_NAMEARGUMENT_H

#include "BaseValueArgument.h"

namespace Chrysalis {
    class SERIALIZABLE(NameArgument): public BaseValueArgument<std::string> {
    public:
        explicit NameArgument() = default;
        explicit NameArgument(const std::string& name): BaseValueArgument(name) {}
    };
    DEFAULT_SERIALIZE_DERIVED_MEMBERS(NameArgument, BaseValueArgument<std::string>)
}

#endif //CHRYSALIS_NAMEARGUMENT_H