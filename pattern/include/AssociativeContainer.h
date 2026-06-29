#ifndef CHRYSALIS_ASSOCIATIVECONTAINER_H
#define CHRYSALIS_ASSOCIATIVECONTAINER_H

#include <vector>

namespace Chrysalis {
    template<typename T>
    class AssociativeContainer {
        SERIALIZE(items_)
    public:
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
}

#endif //CHRYSALIS_ASSOCIATIVECONTAINER_H