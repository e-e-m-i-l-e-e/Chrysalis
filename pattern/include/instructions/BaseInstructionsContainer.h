#ifndef CHRYSALIS_BASEINSTRUCTIONSCONTAINER_H
#define CHRYSALIS_BASEINSTRUCTIONSCONTAINER_H

#include <boost/optional/optional.hpp>

#include "../BaseContainer.h"
#include "BaseInstruction.h"

namespace Chrysalis {
    template<typename T>
    requires std::derived_from<T, BaseInstruction>
    class BaseInstructionsContainer: public BaseInstruction, public BaseContainer<T> {
    protected:
        explicit BaseInstructionsContainer() = default;
    public:
        void add(T* item) override {
            BaseContainer<T>::add(item);
            item->execute();
        }
        void execute() override {
            this->call(&BaseInstruction::execute);
        }
    };
}

#endif //CHRYSALIS_BASEINSTRUCTIONSCONTAINER_H