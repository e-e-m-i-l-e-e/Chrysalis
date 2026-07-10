#ifndef CHRYSALIS_COMPOSITIVECONTAINER_H
#define CHRYSALIS_COMPOSITIVECONTAINER_H

#include "AssociativeContainer.h"

namespace Chrysalis {
    template<typename T>
    class CompositiveContainer: public AssociativeContainer<T> {
    public:
        ~CompositiveContainer() override {
            for (const auto& item: *this) delete item;
        }
    };
    SERIALIZE_DERIVED_CONSTRUCTION_T(CompositiveContainer, AssociativeContainer)
}

#endif //CHRYSALIS_COMPOSITIVECONTAINER_H