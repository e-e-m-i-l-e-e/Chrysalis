#ifndef CHRYSALIS_BASECONTAINER_H
#define CHRYSALIS_BASECONTAINER_H

#include <list>

#include "PatternSpace.h"

namespace Chrysalis {
    template<typename T>
    class BaseContainer {
    protected:
        explicit BaseContainer() = default;

        template<typename Fn, typename... Args>
        void call(Fn function, Args&&... args) const {
            for (const auto& item : data_) {
                (item->*function)(std::forward<Args>(args)...);
            }
        }
        std::list<T*>::const_iterator begin() const {
            return data_.cbegin();
        }
        std::list<T*>::const_iterator end() const {
            return data_.cend();
        }
    public:
        virtual ~BaseContainer() {
            for (const auto& item: data_) delete item;
        }
        void add(T* item) {
            data_.push_back(item);
        }
    private:
        std::list<T*> data_;
    };
}

#endif //CHRYSALIS_BASECONTAINER_H