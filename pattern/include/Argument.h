#ifndef CHRYSALIS_BASEARGUMENT_H
#define CHRYSALIS_BASEARGUMENT_H

#include <boost/optional/optional.hpp>

template<typename T>
class Argument {
public:
    explicit Argument() = default;
    explicit Argument(T argument): argument_(argument) {}

    virtual ~Argument() = default;

    bool hasArgument() {
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

#endif //CHRYSALIS_BASEARGUMENT_H