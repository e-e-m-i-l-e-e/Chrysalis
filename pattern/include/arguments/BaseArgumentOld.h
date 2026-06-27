#ifndef CHRYSALIS_BASEARGUMENTOLD_H
#define CHRYSALIS_BASEARGUMENTOLD_H

#include <boost/optional/optional.hpp>

#include "serialization.h"

namespace Chrysalis {
    template<typename T>
    class SERIALIZABLE_T(BaseArgumentOld, T) {
        PROVIDE_SERIALIZATION_ACCESS_T(BaseArgumentOld)
    protected:
        explicit BaseArgumentOld() = default;
        explicit BaseArgumentOld(T argument): argument_(argument) {}
        explicit BaseArgumentOld(boost::optional<T> argument): argument_(argument) {}
    public:
        virtual ~BaseArgumentOld() = default;

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
    SIMPLE_SERIALIZE_MEMBERS_T(BaseArgumentOld, T, argument_)
}

#endif //CHRYSALIS_BASEARGUMENTOLD_H