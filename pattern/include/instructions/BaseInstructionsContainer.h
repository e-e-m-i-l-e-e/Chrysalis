#ifndef CHRYSALIS_BASEINSTRUCTIONSCONTAINER_H
#define CHRYSALIS_BASEINSTRUCTIONSCONTAINER_H

#include <boost/optional/optional.hpp>

#include "BaseContainer.h"
#include "BaseInstruction.h"

namespace Chrysalis {
    template<typename T>
    requires std::derived_from<T, BaseInstruction>
    class SERIALIZABLE_T_DERIVED_FROM(BaseInstructionsContainer, T, BaseInstruction): public BaseInstruction, public BaseContainer<T> {
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
    DEFAULT_SERIALIZE_DERIVED_MEMBERS_T(BaseInstructionsContainer, T, BaseContainer)
}

#endif //CHRYSALIS_BASEINSTRUCTIONSCONTAINER_H