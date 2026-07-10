#ifndef CHRYSALIS_SCOPED_H
#define CHRYSALIS_SCOPED_H

#include "NamedElementsContainer.h"

namespace Chrysalis {
    template<typename T>
    class ScopedNamedElementsContainer: public NamedElementsContainer<T> {
        PROVIDE_SERIALIZATION_ACCESS_T(ScopedNamedElementsContainer)
    public:
        explicit ScopedNamedElementsContainer(): parent_(nullptr) {}
        explicit ScopedNamedElementsContainer(const ScopedNamedElementsContainer* parent): parent_(parent) {}

        [[nodiscard]] bool has(const std::string& name) const override {
            if (NamedElementsContainer<T>::has(name)) return true;
            if (parent_) return parent_->has(name);
            return false;
        }
        T* get(const std::string& name) const override {
            if (NamedElementsContainer<T>::has(name)) return NamedElementsContainer<T>::get(name);
            if (parent_) return parent_->get(name);
            return nullptr;
        }
    private:
        const ScopedNamedElementsContainer* parent_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION_T(ScopedNamedElementsContainer, NamedElementsContainer, parent_)
}

#endif //CHRYSALIS_SCOPED_H