#ifndef CHRYSALIS_ASSOCIATIVECONTAINER_H
#define CHRYSALIS_ASSOCIATIVECONTAINER_H

#include <vector>

#include "serialization.h"

namespace Chrysalis {
    template<typename T>
    class AssociativeContainer {
        PROVIDE_SERIALIZATION_ACCESS_T(AssociativeContainer)
    public:
        explicit AssociativeContainer() = default;
        explicit AssociativeContainer(std::initializer_list<T*> items): items_(items) {}

        virtual ~AssociativeContainer() = default;

        virtual void add(T* item) {
            items_.push_back(item);
        }
        size_t count() const {
            return items_.size();
        }
        std::vector<T*>::const_iterator begin() const {
            return items_.begin();
        }
        std::vector<T*>::const_iterator end() const {
            return items_.end();
        }
        T* operator[](size_t index) const {
            return items_[index];
        }
    private:
        std::vector<T*> items_;
    };
    template <class Archive, typename T>
    void serialize(Archive& archive, AssociativeContainer<T>& obj, const unsigned int version)
    {
        archive & obj.items_;
    }

    template <class Archive, typename T>
    void save_construct_data(Archive& archive, const AssociativeContainer<T>* obj, const unsigned int)
    {
        archive & obj->items_;
    }

    template <class Archive, typename T>
    void load_construct_data(Archive& archive, AssociativeContainer<T>* obj, const unsigned int)
    {
        decltype(obj->items_) items_;
        archive >> items_;
        ::new(obj) AssociativeContainer<T>();
    }
}

#endif //CHRYSALIS_ASSOCIATIVECONTAINER_H