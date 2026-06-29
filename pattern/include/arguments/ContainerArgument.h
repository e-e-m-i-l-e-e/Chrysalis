#ifndef CHRYSALIS_BASEOWNINGCONTAINERARGUMENT_H
#define CHRYSALIS_BASEOWNINGCONTAINERARGUMENT_H

#include "BaseContainerArgument.h"

namespace Chrysalis {
    template<typename T>
    class ContainerArgument: public BaseContainerArgument<T> {
    public:
        ContainerArgument() = default;
        ~ContainerArgument() {
            for (const auto& item: *this) {
                delete item;
            }
        }
    };
    namespace args {
        template<typename T>
        using container = ContainerArgument<T>;
    }
}

#endif //CHRYSALIS_BASEOWNINGCONTAINERARGUMENT_H