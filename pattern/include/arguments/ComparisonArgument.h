#ifndef CHRYSALIS_CONDITIONARGUMENT_H
#define CHRYSALIS_CONDITIONARGUMENT_H

#define COMPARISONS (Equal)(NotEqual)(Greater)(GreaterEqual)(Less)(LessEqual)

#include "BaseCalculatedArgument.h"

namespace Chrysalis {
    class ComparisonArgument: public BaseCalculatedArgument<bool> {
        SERIALIZE_DERIVED_FROM(BaseCalculatedArgument)
    protected:
        explicit ComparisonArgument(const args::number* value1, const args::number* value2);
    public:
        ~ComparisonArgument() override;

        #define FORWARD_DECLARE(r, data, Name) class Name;
        BOOST_PP_SEQ_FOR_EACH(FORWARD_DECLARE, _, COMPARISONS)
        #undef FORWARD_DECLARE

        [[nodiscard]] bool isValid() const override;
    protected:
        bool calculate() const override;
        virtual bool evaluate(double a, double b) const = 0;

        const args::number* value1_;
        const args::number* value2_;
    };
    namespace args {
        using compare = ComparisonArgument;
    }

    const ComparisonArgument* operator==(const args::number& value1, const args::number& value2);
    const ComparisonArgument* operator!=(const args::number& value1, const args::number& value2);
    const ComparisonArgument* operator>(const args::number& value1, const args::number& value2);
    const ComparisonArgument* operator>=(const args::number& value1, const args::number& value2);
    const ComparisonArgument* operator<(const args::number& value1, const args::number& value2);
    const ComparisonArgument* operator<=(const args::number& value1, const args::number& value2);

    #define DECLARE_COMPARISON(r, data, Name)                                                                          \
    class ComparisonArgument::Name: public ComparisonArgument {                                                        \
        PROVIDE_SERIALIZATION_ACCESS(ComparisonArgument::Name)                                                         \
    public:                                                                                                            \
        explicit Name(const args::number* value1, const args::number* value2)                                          \
                 : ComparisonArgument(value1, value2) {}                                                               \
    protected:                                                                                                         \
        bool evaluate(double a, double b) const override;                                                              \
    };                                                                                                                 \
    SERIALIZE_DERIVED_CONSTRUCTION(ComparisonArgument::Name, ComparisonArgument, value1_, value2_);
    BOOST_PP_SEQ_FOR_EACH(DECLARE_COMPARISON, _, COMPARISONS)
    #undef DECLARE_COMPARISON
}

#endif //CHRYSALIS_CONDITIONARGUMENT_H