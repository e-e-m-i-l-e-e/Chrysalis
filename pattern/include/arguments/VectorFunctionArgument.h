#ifndef CHRYSALIS_VECTORFUNCTIONARGUMENT_H
#define CHRYSALIS_VECTORFUNCTIONARGUMENT_H

#include "BaseCalculatedArgument.h"
#include "arguments/VectorFunction.h"
#include "arguments/BaseArgument.h"
#include "arguments/PointArgument.h"

namespace Chrysalis {
    /**
     * @uml{note[top] Syntax samples:
     * (A -> B).length
     * (A ("Pattern 1") -> "A 1").angle
     * }
     */
    class VectorFunctionArgument: public BaseCalculatedArgument<double> {
        PROVIDE_SERIALIZATION_ACCESS(VectorFunctionArgument)
    public:
        explicit VectorFunctionArgument(const args::point* from, const args::point* to,
                                        const VectorFunction* function);
        ~VectorFunctionArgument() override;

        bool isValid() const override;
    protected:
        double calculate() const override;
    private:
        /// @uml{composition}
        const args::point* from_;
        /// @uml{composition}
        const args::point* to_;
        /// @uml{composition}
        const VectorFunction* function_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(VectorFunctionArgument, BaseCalculatedArgument<double>, from_, to_, function_)
}

#endif //CHRYSALIS_VECTORFUNCTIONARGUMENT_H