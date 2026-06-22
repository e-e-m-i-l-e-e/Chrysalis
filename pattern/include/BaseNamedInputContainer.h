#ifndef CHRYSALIS_BASEINPUTCONTAINER_H
#define CHRYSALIS_BASEINPUTCONTAINER_H

#include <unordered_map>

#include "BaseContainer.h"
#include "BaseNamedInput.h"

namespace Chrysalis {
    template<typename T>
    requires std::derived_from<T, BaseNamedInput>
    class SERIALIZABLE_T_DERIVED_FROM(BaseInputContainer, T, BaseNamedInput): public BaseContainer<T> {
        PROVIDE_SERIALIZATION_ACCESS_T(BaseInputContainer)
    protected:
        explicit BaseInputContainer() = default;

    public:
        void add(T* item) override {
            BaseContainer<T>::add(item);
            names_[item->getName()] = item;
            if (item->hasAlias()) names_[item->getAlias()] = item;
        }
        T* get(const std::string& name) const {
            return names_.at(name);
        }
    private:
        std::unordered_map<std::string, T*> names_;
    };
    SERIALIZE_DERIVED_MEMBERS_T(BaseInputContainer, T, BaseContainer, names_)
}

#endif //CHRYSALIS_BASEINPUTCONTAINER_H