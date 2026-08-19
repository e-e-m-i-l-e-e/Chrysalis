#ifndef CHRYSALIS_CONDITIONALARGUMENT_H
#define CHRYSALIS_CONDITIONALARGUMENT_H

#include "arguments/BaseArgument.h"
#include "arguments/BaseCalculatedArgument.h"

/** @defgroup Arguments Arguments
 *  @{
 */
namespace Chrysalis {
    class ConditionalArgument: public BaseCalculatedArgument<double> {
        PROVIDE_SERIALIZATION_ACCESS(ConditionalArgument)
    public:
        explicit ConditionalArgument(const args::condition* condition,
                                     args::number&& positive, args::number&& negative);
        ~ConditionalArgument() override;
    protected:
        std::expected<double, Error> calculate() const override;
    private:
        const args::condition* condition_;
        args::number positive_;
        args::number negative_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(ConditionalArgument, BaseCalculatedArgument<double>, condition_, positive_, negative_)
    namespace args {
        using conditional = ConditionalArgument;
    }
}
/**@}*/

#endif //CHRYSALIS_CONDITIONALARGUMENT_H