#ifndef CHRYSALIS_VECTORFUNCTIONARGUMENT_H
#define CHRYSALIS_VECTORFUNCTIONARGUMENT_H

#include "arguments/PatternPointArgument.h"
#include "arguments/BaseCalculatedArgument.h"

#define VECTOR_FUNCTIONS (Length)(Angle)

namespace Chrysalis {
/** @defgroup Arguments Arguments
 *  @{
 */
    /**
     * @uml{note[top] Syntax samples:
     * (A -> B).length
     * (A ("Pattern 1") -> "A 1").angle
     * }
     */
    class VectorFunctionArgument: public BaseCalculatedArgument<double> {
        SERIALIZE_DERIVED_FROM(BaseCalculatedArgument)
    protected:
        explicit VectorFunctionArgument(const args::point* from, const args::point* to);
    public:
        ~VectorFunctionArgument() override;

#define FORWARD_DECLARE(r, data, Name) class Name;
        BOOST_PP_SEQ_FOR_EACH(FORWARD_DECLARE, _, VECTOR_FUNCTIONS)
#undef FORWARD_DECLARE
    protected:
        std::expected<double, Error> calculate() const override;
        virtual std::expected<double, Error> evaluate(const CG::Point& from, const CG::Point& to) const = 0;

        /// @uml{composition}
        const args::point* from_;
        /// @uml{composition}
        const args::point* to_;
    };

    #define DECLARE_VECTOR_FUNCTION(r, data, Name)                                                                     \
    class VectorFunctionArgument::Name: public VectorFunctionArgument {                                                \
        PROVIDE_SERIALIZATION_ACCESS(VectorFunctionArgument::Name)                                                     \
    public:                                                                                                            \
        explicit Name(const args::point* from, const args::point* to): VectorFunctionArgument(from, to) {}             \
    protected:                                                                                                         \
        std::expected<double, Error> evaluate(const CG::Point& from, const CG::Point& to) const override;                                    \
    };                                                                                                                 \
    SERIALIZE_DERIVED_CONSTRUCTION(VectorFunctionArgument::Name, VectorFunctionArgument, from_, to_);
    BOOST_PP_SEQ_FOR_EACH(DECLARE_VECTOR_FUNCTION, _, VECTOR_FUNCTIONS)
    #undef DECLARE_VECTOR_FUNCTION
}

#endif //CHRYSALIS_VECTORFUNCTIONARGUMENT_H