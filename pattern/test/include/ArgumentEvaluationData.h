#ifndef CHRYSALIS_ARGUMENTSEVALUATIONDATA_H
#define CHRYSALIS_ARGUMENTSEVALUATIONDATA_H

#include "arguments/Argument.h"

namespace Chrysalis {
    class ArgumentEvaluationData {
    public:
        explicit ArgumentEvaluationData(const BaseArgument<double>* expression, std::string&& expressionText, double expected);

        [[nodiscard]] const BaseArgument<double>* expression() const;
        [[nodiscard]] const std::string& expressionText() const;
        [[nodiscard]] double expected() const;
    private:
        const BaseArgument<double>* expression_;
        std::string expressionText_;
        double expected_;
    };
    template <std::size_t I>
    decltype(auto) get(const ArgumentEvaluationData& data) {
        if constexpr (I == 0) return data.expression();
        else if constexpr (I == 1) return data.expressionText();
        else if constexpr (I == 2) return data.expected();
    }
}

template <>
struct std::tuple_size<Chrysalis::ArgumentEvaluationData>: std::integral_constant<std::size_t, 3> {};

template <std::size_t I>
struct std::tuple_element<I, Chrysalis::ArgumentEvaluationData> {
    using type = std::tuple_element_t<I, std::tuple<const Chrysalis::BaseArgument<double>*, std::string, double>>;
};

#endif //CHRYSALIS_ARGUMENTSEVALUATIONDATA_H
