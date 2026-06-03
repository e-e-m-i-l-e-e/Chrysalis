#ifndef CHRYSALIS_BASECONTAINER_H
#define CHRYSALIS_BASECONTAINER_H

#include <list>

#include "serialization.h"

namespace Chrysalis {
    template<typename T>
    class SERIALIZABLE(BaseContainer) {
    protected:
        explicit BaseContainer() = default;

        template<typename Fn, typename... Args>
        void call(Fn function, Args&&... args) const {
            for (const auto& item : data_) {
                (item->*function)(std::forward<Args>(args)...);
            }
        }
    public:
        virtual ~BaseContainer() {
            for (const auto& item: data_) delete item;
        }
        T* at(size_t index) const {
            return *std::next(data_.begin(), index);
        }
        size_t count() const {
            return data_.size();
        }
        virtual void add(T* item) {
            data_.push_back(item);
        }
    private:
        ///@uml{composition}
        std::list<T*> data_;
    };
}

#endif //CHRYSALIS_BASECONTAINER_H