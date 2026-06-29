#ifndef CHRYSALIS_BASECONTAINERARGUMENT_H
#define CHRYSALIS_BASECONTAINERARGUMENT_H

#include <vector>
#include <algorithm>

#include "serialization.h"

namespace Chrysalis {
    template<typename T>
    class BaseContainerArgument {
        SERIALIZE(items_)
    protected:
        explicit BaseContainerArgument() = default;
    public:
        std::vector<T*>::const_iterator begin() const {
            return items_.cbegin();
        }
        std::vector<T*>::const_iterator end() const {
            return items_.cend();
        }
        void add(T* item) {
            items_.push_back(item);
        }
        [[nodiscard]] bool empty() const {
            return items_.empty();
        }
        template<typename... Args>
        bool all(bool (T::* check)(Args...) const, std::type_identity_t<Args>... args) const {
            return std::all_of(items_.begin(), items_.end(), [&](const T* item) {
                return (item->*check)(args...);
            });
        }
        template<typename R, typename... Args>
        R onAny(R (T::* method)(Args...) const, std::type_identity_t<Args>... args) const {
            return (items_.front()->*method)(args...);
        }
    private:
        std::vector<T*> items_;
    };
}

#endif //CHRYSALIS_BASECONTAINERARGUMENT_H