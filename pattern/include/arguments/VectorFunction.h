#ifndef CHRYSALIS_VECTORFUNCTION_H
#define CHRYSALIS_VECTORFUNCTION_H

#include <boost/serialization/export.hpp>

#include "arguments/NameArgument.h"
#include "arguments/PatternArgument.h"

#define VECTOR_FUNCTIONS (Length)(Angle)

#define FORWARD_DECLARE_VECTOR_FUNCTION(r, data, Name)                                                                 \
class Name;

#define DECLARE_VECTOR_FUNCTION(r, data, Name)                                                                         \
namespace Chrysalis {                                                                                                  \
    class VectorFunction::Name: public VectorFunction {                                                                \
    public:                                                                                                            \
        boost::optional<double> evaluate(const name* pointFrom, const pattern* patternFrom,                            \
                                         const name* pointTo, const pattern* patternTo) const override;                \
    };                                                                                                                 \
    SERIALIZE_DERIVED_MEMBERS(VectorFunction::Name, VectorFunction)                                                    \
}                                                                                                                      \
BOOST_CLASS_EXPORT_KEY(Chrysalis::VectorFunction::Name)

namespace Chrysalis {
    using name = NameArgument;
    using pattern = PatternArgument;

    class EMPTY_SERIALIZABLE(VectorFunction) {
    protected:
        explicit VectorFunction() = default;
    public:
        virtual ~VectorFunction() = default;

        BOOST_PP_SEQ_FOR_EACH(FORWARD_DECLARE_VECTOR_FUNCTION, _, VECTOR_FUNCTIONS)

        virtual boost::optional<double> evaluate(const name* pointFrom, const pattern* patternFrom,
                                                 const name* pointTo, const pattern* patternTo) const = 0;
    protected:
        static boost::optional<double> evaluate(const name* pointFrom, const pattern* patternFrom,
                                                const name* pointTo, const pattern* patternTo,
                                                const std::function<double(const Point& from, const Point& to)>& evaluator);
    };
}

BOOST_PP_SEQ_FOR_EACH(DECLARE_VECTOR_FUNCTION, _, VECTOR_FUNCTIONS)

#endif //CHRYSALIS_VECTORFUNCTION_H