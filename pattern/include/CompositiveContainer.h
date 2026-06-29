#ifndef CHRYSALIS_COMPOSITIVECONTAINER_H
#define CHRYSALIS_COMPOSITIVECONTAINER_H

#include "AssociativeContainer.h"

namespace Chrysalis {
    template<typename T>
    class CompositiveContainer: public AssociativeContainer<T> {
        SERIALIZE_DERIVED_FROM(AssociativeContainer<T>)
    public:
        ~CompositiveContainer() override {
            for (const auto& item: *this) delete item;
        }
    };
}

#endif //CHRYSALIS_COMPOSITIVECONTAINER_H