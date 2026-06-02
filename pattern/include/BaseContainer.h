#ifndef CHRYSALIS_BASECONTAINER_H
#define CHRYSALIS_BASECONTAINER_H

#include <list>

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
    public:
        virtual ~BaseContainer() {
            for (const auto& item: data_) delete item;
        }
        virtual void add(T* item) {
            data_.push_back(item);
        }
    private:
        std::list<T*> data_;
    };
}

#endif //CHRYSALIS_BASECONTAINER_H