#ifndef CHRYSALIS_BASECONTAINERARGUMENT_H
#define CHRYSALIS_BASECONTAINERARGUMENT_H

#include <vector>

namespace Chrysalis {
    template<typename T>
    class BaseContainerArgument {
    protected:
        explicit BaseContainerArgument() = default;
    public:
        virtual ~BaseContainerArgument() {
            for (const auto& item: items_) {
                delete item;
            }
        }

        void add(T* item) {
            items_.push_back(item);
        }
    private:
        std::vector<T*> items_;
    };
}

#endif //CHRYSALIS_BASECONTAINERARGUMENT_H