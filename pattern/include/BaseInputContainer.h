#ifndef CHRYSALIS_BASEINPUTCONTAINER_H
#define CHRYSALIS_BASEINPUTCONTAINER_H

#include <unordered_map>

#include "BaseContainer.h"

namespace Chrysalis {
    template<typename T>
    class SERIALIZABLE_T(BaseInputContainer, T): public BaseContainer<T> {
        PROVIDE_SERIALIZATION_ACCESS_T(BaseInputContainer)
    protected:
        explicit BaseInputContainer() = default;

        void add(const std::string& name, T* item) {
            BaseContainer<T>::add(item);
            names_[name] = item;
        }
    public:
        void add(T* item) override = 0;
        T* get(const std::string& name) const {
            return names_.at(name);
        }
    private:
        std::unordered_map<std::string, T*> names_;
    };
    SERIALIZE_DERIVED_MEMBERS_T(BaseInputContainer, T, BaseContainer, names_)
}

#endif //CHRYSALIS_BASEINPUTCONTAINER_H