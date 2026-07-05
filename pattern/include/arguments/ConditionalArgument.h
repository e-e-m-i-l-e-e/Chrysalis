#ifndef CHRYSALIS_CONDITIONALARGUMENT_H
#define CHRYSALIS_CONDITIONALARGUMENT_H

#include "arguments/BaseArgument.h"
#include "arguments/BaseCalculatedArgument.h"

namespace Chrysalis {
    class ConditionalArgument: public BaseCalculatedArgument<double> {
        PROVIDE_SERIALIZATION_ACCESS(ConditionalArgument)
    public:
        explicit ConditionalArgument(const args::condition* condition,
                                     const args::number* positive, const args::number* negative);
        ~ConditionalArgument() override;

        [[nodiscard]] bool isValid() const override;
    protected:
        double calculate() const override;
    private:
        const args::condition* condition_;
        const args::number* positive_;
        const args::number* negative_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(ConditionalArgument, BaseCalculatedArgument<double>, condition_, positive_, negative_)
    namespace args {
        using conditional = ConditionalArgument;
    }
}

#endif //CHRYSALIS_CONDITIONALARGUMENT_H