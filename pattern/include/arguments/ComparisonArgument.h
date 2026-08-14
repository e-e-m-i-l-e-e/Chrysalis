#ifndef CHRYSALIS_COMPARISONARGUMENT_H
#define CHRYSALIS_COMPARISONARGUMENT_H

#define COMPARISONS (Equal)(NotEqual)(Greater)(GreaterEqual)(Less)(LessEqual)

#include "BaseCalculatedArgument.h"

namespace Chrysalis {
    /**
     * @defgroup Arguments
     * @{
     */
    class ComparisonArgument: public BaseCalculatedArgument<bool> {
        SERIALIZE_DERIVED_FROM(BaseCalculatedArgument)
    protected:
        explicit ComparisonArgument(args::number&& value1, args::number&& value2);
    public:
        #define FORWARD_DECLARE(r, data, Name) class Name;
        BOOST_PP_SEQ_FOR_EACH(FORWARD_DECLARE, _, COMPARISONS)
        #undef FORWARD_DECLARE
    protected:
        std::expected<bool, Error> calculate() const override;
        virtual bool evaluate(double a, double b) const = 0;

        args::number value1_;
        args::number value2_;
    };
    namespace args {
        using compare = ComparisonArgument;
    }

    #define DECLARE_COMPARISON(r, data, Name)                                                                          \
    class ComparisonArgument::Name: public ComparisonArgument {                                                        \
        PROVIDE_SERIALIZATION_ACCESS(ComparisonArgument::Name)                                                         \
    public:                                                                                                            \
        explicit Name(args::number&& value1, args::number&& value2)                                                    \
                 : ComparisonArgument(std::move(value1), std::move(value2)) {}                                         \
    protected:                                                                                                         \
        bool evaluate(double a, double b) const override;                                                              \
    };                                                                                                                 \
    SERIALIZE_DERIVED_CONSTRUCTION(ComparisonArgument::Name, ComparisonArgument, value1_, value2_);
    BOOST_PP_SEQ_FOR_EACH(DECLARE_COMPARISON, _, COMPARISONS)
    #undef DECLARE_COMPARISON
}

#endif //CHRYSALIS_COMPARISONARGUMENT_H