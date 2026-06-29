#ifndef CHRYSALIS_BASEINSTRUCTIONSCONTAINER_H
#define CHRYSALIS_BASEINSTRUCTIONSCONTAINER_H

#include "BaseInstruction.h"
#include "CompositiveContainer.h"

namespace Chrysalis {
    template<typename T>
    requires std::derived_from<T, BaseInstruction>
    class BaseInstructionsContainer: public BaseInstruction, public CompositiveContainer<T> {
        SERIALIZE_DERIVED_FROM(CompositiveContainer<T>)
    public:
        void add(T* item) override {
            CompositiveContainer<T>::add(item);
            item->execute();
        }
        void execute() override {
            for (const auto& instruction: *this) {
                instruction->execute();
            }
        }
    };
}

#endif //CHRYSALIS_BASEINSTRUCTIONSCONTAINER_H