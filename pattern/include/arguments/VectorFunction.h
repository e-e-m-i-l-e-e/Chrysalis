#ifndef CHRYSALIS_VECTORFUNCTION_H
#define CHRYSALIS_VECTORFUNCTION_H

#include <boost/serialization/export.hpp>

#include "arguments/PointArgument.h"

#define VECTOR_FUNCTIONS (Length)(Angle)

namespace Chrysalis {
    class VectorFunction {
        SERIALIZED
    protected:
        explicit VectorFunction() = default;
    public:
        virtual ~VectorFunction() = default;

#define FORWARD_DECLARE(r, data, Name) class Name;
        BOOST_PP_SEQ_FOR_EACH(FORWARD_DECLARE, _, VECTOR_FUNCTIONS)
#undef FORWARD_DECLARE

        virtual double evaluate(const args::point* from, const args::point* to) const = 0;
    protected:
        static double evaluate(const args::point* from, const args::point* to,
                               const std::function<double(const Point& from, const Point& to)>& evaluator);
    };
}

#define DECLARE_VECTOR_FUNCTION(r, data, Name)                                                                         \
namespace Chrysalis {                                                                                                  \
    class VectorFunction::Name: public VectorFunction {                                                                \
        SERIALIZE_DERIVED_FROM(VectorFunction)                                                                         \
    public:                                                                                                            \
        double evaluate(const args::point* from, const args::point* to) const override;                                \
    };                                                                                                                 \
}                                                                                                                      \
BOOST_CLASS_EXPORT_KEY(Chrysalis::VectorFunction::Name)
BOOST_PP_SEQ_FOR_EACH(DECLARE_VECTOR_FUNCTION, _, VECTOR_FUNCTIONS)
#undef DECLARE_VECTOR_FUNCTION

#endif //CHRYSALIS_VECTORFUNCTION_H