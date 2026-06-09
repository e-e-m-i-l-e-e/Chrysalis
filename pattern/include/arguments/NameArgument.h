#ifndef CHRYSALIS_NAMEARGUMENT_H
#define CHRYSALIS_NAMEARGUMENT_H

#include "BaseArgument.h"

namespace Chrysalis {
    class SERIALIZABLE(NameArgument): public BaseArgument<std::string> {
    public:
        explicit NameArgument() = default;
        explicit NameArgument(const std::string& name): BaseArgument(name) {}
    };
    DEFAULT_SERIALIZE_DERIVED_MEMBERS(NameArgument, BaseArgument<std::string>)
}

#endif //CHRYSALIS_NAMEARGUMENT_H