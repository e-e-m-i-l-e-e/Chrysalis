#ifndef CHRYSALIS_PATTERNSCONTAINERARGUMENT_H
#define CHRYSALIS_PATTERNSCONTAINERARGUMENT_H

#include "PatternSpace.h"

/** @defgroup Arguments Arguments
 *  @{
 */
namespace Chrysalis {
    class PatternsContainerArgument: public AssociativeContainer<PatternSpace> {
        SERIALIZE_DERIVED_FROM(AssociativeContainer)
    public:
        explicit PatternsContainerArgument() = default;
        explicit PatternsContainerArgument(std::initializer_list<PatternSpace*>&& items): AssociativeContainer(items) {}

        [[nodiscard]] bool empty() const {
            return count() == 0;
        }
        template<typename... Args>
        bool all(bool (PatternSpace::* check)(Args...) const, std::type_identity_t<Args>... args) const {
            return std::all_of(begin(), end(), [&](const PatternSpace* item) {
                return (item->*check)(args...);
            });
        }
        template<typename R, typename... Args>
        R onAny(R (PatternSpace::* method)(Args...) const, std::type_identity_t<Args>... args) const {
            return (*begin()->*method)(args...);
        }
    };
    namespace args {
        using patterns = PatternsContainerArgument;
    }
}
/**@}*/

#endif //CHRYSALIS_PATTERNSCONTAINERARGUMENT_H