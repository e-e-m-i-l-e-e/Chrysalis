#ifndef CHRYSALIS_NAMEDELEMENTSCONTAINER_H
#define CHRYSALIS_NAMEDELEMENTSCONTAINER_H

#include <unordered_map>

#include "BaseNamedElement.h"
#include "CompositiveContainer.h"

namespace Chrysalis {
    template<typename T>
    requires std::derived_from<T, BaseNamedElement>
    class NamedElementsContainer: public CompositiveContainer<T> {
        SERIALIZE_DERIVED_FROM(CompositiveContainer<T>, names_)
    public:
        [[nodiscard]] virtual bool has(const std::string& name) const {
            return names_.contains(name);
        }
        void add(T* item) override {
            CompositiveContainer<T>::add(item);
            names_[item->getName()] = item;
            if (item->hasAlias()) names_[item->getAlias()] = item;
        }
        virtual T* get(const std::string& name) const {
            return names_.at(name);
        }
    private:
        std::unordered_map<std::string, T*> names_;
    };
}

#endif //CHRYSALIS_NAMEDELEMENTSCONTAINER_H
