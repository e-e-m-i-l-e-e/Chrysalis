#ifndef CHRYSALIS_OPTIONARGUMENT_H
#define CHRYSALIS_OPTIONARGUMENT_H

#include "Option.h"
#include "arguments/Argument.h"
#include "arguments/BaseCalculatedArgument.h"

namespace Chrysalis {
    class OptionArgument: public BaseCalculatedArgument<bool> {
        PROVIDE_SERIALIZATION_ACCESS(OptionArgument)
    public:
        explicit OptionArgument(const OptionsContainer* options, const args::name* name);
        ~OptionArgument() override;

        [[nodiscard]] bool isValid() const override;
    protected:
        bool calculate() const override;
    private:
        const OptionsContainer* options_;
        /// @uml{composition}
        const args::name* name_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(OptionArgument, BaseCalculatedArgument<bool>, options_, name_)
}

#endif //CHRYSALIS_OptionARGUMENT_H