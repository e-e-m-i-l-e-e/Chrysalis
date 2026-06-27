#ifndef CHRYSALIS_VECTORFUNCTIONARGUMENT_H
#define CHRYSALIS_VECTORFUNCTIONARGUMENT_H

#include "BaseCalculatedArgument.h"
#include "arguments/VectorFunction.h"
#include "arguments/BaseArgument.h"

namespace Chrysalis {
    /**
     * @uml{note[top] Syntax samples:
     * (A -> B).length
     * (A ("Pattern 1") -> "A 1").angle
     * }
     */
    class SERIALIZABLE(VectorFunctionArgument): public BaseCalculatedArgument<double> {
        PROVIDE_SERIALIZATION_ACCESS(VectorFunctionArgument)
    public:
        explicit VectorFunctionArgument(const name* pointFrom, const pattern* patternFrom,
                                        const name* pointTo, const pattern* patternTo,
                                        const VectorFunction* function);
        ~VectorFunctionArgument() override;

        bool isValid() const override;
    protected:
        double calculate() const override;
    private:
        /// @uml{composition}
        const name* pointFrom_;
        /// @uml{composition}
        const pattern* patternFrom_;
        /// @uml{composition}
        const name* pointTo_;
        /// @uml{composition}
        const pattern* patternTo_;
        /// @uml{composition}
        const VectorFunction* function_;
    };
    SIMPLE_SERIALIZE_DERIVED_MEMBERS(VectorFunctionArgument, BaseCalculatedArgument<double>, pointFrom_, patternFrom_, pointTo_, patternTo_, function_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::VectorFunctionArgument)

#endif //CHRYSALIS_VECTORFUNCTIONARGUMENT_H