#ifndef CHRYSALIS_BASEARGUMENT_H
#define CHRYSALIS_BASEARGUMENT_H

#include <boost/optional/optional.hpp>

namespace Chrysalis {
    template<typename T>
    class BaseArgument {
    protected:
        explicit BaseArgument() = default;
        explicit BaseArgument(T argument): argument_(argument) {}
        explicit BaseArgument(boost::optional<T> argument): argument_(argument) {}
    public:
        virtual ~BaseArgument() = default;

        [[nodiscard]] bool hasArgument() const {
            return argument_.has_value();
        }
        void setArgument(T value) {
            argument_ = value;
        }
        void resetArgument() {
            argument_.reset();
        }
        [[nodiscard]] const T& getArgument() const {
            return argument_.value();
        }
    protected:
        boost::optional<T> argument_;
    };
}

#endif //CHRYSALIS_BASEARGUMENT_H