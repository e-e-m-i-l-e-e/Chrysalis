#ifndef CHRYSALIS_OPTIONARGUMENT_H
#define CHRYSALIS_OPTIONARGUMENT_H

#include "Option.h"
#include "arguments/Argument.h"
#include "arguments/BaseCalculatedArgument.h"

/** @defgroup Arguments Arguments
 *  @{
 */
namespace Chrysalis {
    class OptionArgument: public BaseCalculatedArgument<bool> {
        PROVIDE_SERIALIZATION_ACCESS(OptionArgument)
    public:
        explicit OptionArgument(const OptionsContainer* options, args::name&& name);
    protected:
        std::expected<bool, Error> calculate() const override;
    private:
        const OptionsContainer* options_;
        /// @uml{composition}
        args::name name_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(OptionArgument, BaseCalculatedArgument<bool>, options_, name_)
}
/**@}*/

#endif //CHRYSALIS_OptionARGUMENT_H