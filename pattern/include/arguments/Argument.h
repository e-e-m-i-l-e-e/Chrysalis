#ifndef CHRYSALIS_BASEVALIDARGUMENT_H
#define CHRYSALIS_BASEVALIDARGUMENT_H

#include "BaseArgument.h"

namespace Chrysalis {
    template<typename T>
    class Argument: public BaseArgument<T> {
        PROVIDE_SERIALIZATION_ACCESS_T(Argument)
    public:
        explicit Argument(const T& value): value_(value) {}

        [[nodiscard]] std::expected<T, Error> get() const override {
            return value_;
        }
        void set(const T& value) {
            value_ = value;
        }
    private:
        T value_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION_T(Argument, BaseArgument, value_)
    namespace args {
        using name = std::unique_ptr<Argument<std::string>>;
    }
}

#endif // CHRYSALIS_BASEVALIDARGUMENT_H