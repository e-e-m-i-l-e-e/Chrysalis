#ifndef CHRYSALIS_VECTORFUNCTIONARGUMENT_H
#define CHRYSALIS_VECTORFUNCTIONARGUMENT_H

#include "NameArgument.h"
#include "ProjectSpace.h"
#include "NumberArgument.h"
#include "PatternArgument.h"

namespace Chrysalis {
    using name = NameArgument;
    using pattern = PatternArgument;

    struct VectorFunction {
        boost::optional<double> length(const name* pointFrom, const pattern* patternFrom,
                                       const name* pointTo, const pattern* patternTo);
        boost::optional<double> angle(const name* pointFrom, const pattern* patternFrom,
                                      const name* pointTo, const pattern* patternTo);
    private:
        static boost::optional<double> evaluate(const name* pointFrom, const pattern* patternFrom,
                                                const name* pointTo, const pattern* patternTo,
                                                const std::function<double(const Point* from, const Point* to)>& evaluator);
    };
    /**
     * @uml{note[top] Syntax samples:
     * (A -> B).length
     * (A ("Pattern 1") -> "A 1").angle
     * }
     */
    class VectorFunctionArgument: public NumberArgument {
    public:
        explicit VectorFunctionArgument(const name* pointFrom, const pattern* patternFrom,
                                        const name* pointTo, const pattern* patternTo,
                                        boost::optional<double> (VectorFunction::*function)(
                                            const name* pointFrom, const pattern* patternFrom,
                                            const name* pointTo, const pattern* patternTo
                                        ));
        ~VectorFunctionArgument() override;
    private:
        /// @uml{composition}
        const name* pointFrom_;
        /// @uml{composition}
        const pattern* patternFrom_;
        /// @uml{composition}
        const name* pointTo_;
        /// @uml{composition}
        const pattern* patternTo_;
        boost::optional<double> (VectorFunction::*function_)(const name* pointFrom, const pattern* patternFrom,
                                                             const name* pointTo, const pattern* patternTo);
        static inline VectorFunction evaluator;
    };
}

#endif //CHRYSALIS_VECTORFUNCTIONARGUMENT_H