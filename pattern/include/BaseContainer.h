#ifndef CHRYSALIS_BASECONTAINER_H
#define CHRYSALIS_BASECONTAINER_H

#include <list>

namespace Chrysalis {
    template<typename T>
    class BaseContainer {
    protected:
        explicit BaseContainer() = default;
    public:
        virtual ~BaseContainer() {
            for (const auto& item: data_) delete item;
        }
        void add(T* item) {
            data_.push_back(item);
        }
    protected:
        std::list<T*> data_;
    };
}

#endif //CHRYSALIS_BASECONTAINER_H