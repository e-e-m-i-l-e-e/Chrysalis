#ifndef CHRYSALIS_BASEARGUMENT_H
#define CHRYSALIS_BASEARGUMENT_H

#include <memory>
#include <expected>

#include "Error.h"
#include "CompositiveContainer.h"

/** @defgroup Arguments Arguments
 *  @{
 */
namespace Chrysalis {
    template<typename T>
    class BaseArgument {
        SERIALIZED
    protected:
        explicit BaseArgument() = default;
    public:
        virtual ~BaseArgument() = default;

        [[nodiscard]] virtual std::expected<T, Error> get() const = 0;
    };
    namespace args {
        using number = std::unique_ptr<BaseArgument<double>>;
        using condition = BaseArgument<bool>;
        template<typename T>
        using container = CompositiveContainer<T>;
    }
}
/**@}*/

#endif //CHRYSALIS_BASEARGUMENT_H