#ifndef CHRYSALIS_FREEPOINTINSTRUCTION_H
#define CHRYSALIS_FREEPOINTINSTRUCTION_H

#include "ProjectSpace.h"
#include "BasePatternInstruction.h"

#include <boost/serialization/export.hpp>

#include "FreePointInstruction.h"

namespace Chrysalis {
    /**
     * @uml{note[top] Syntax samples:
     * A (1, 1)
     * "A 1" (1.0, 2)
     * A (1 * 2 + 3, param("Circumference of something"))}
     */
    class FreePointInstruction: public BasePatternInstruction {
        PROVIDE_SERIALIZATION_ACCESS(FreePointInstruction)
    public:
        explicit FreePointInstruction(ProjectSpace* space, args::patterns* patterns,
                                      const args::name* pointName, const args::number* x, const args::number* y);
        ~FreePointInstruction() override;

        bool isValid() override;
        void execute() override;
    private:
        const args::name* pointName_;
        const args::number* x_;
        const args::number* y_;
    };
    SERIALIZE_DERIVED_CONSTRUCTION(FreePointInstruction, BasePatternInstruction, space_, patterns_, pointName_, x_, y_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::FreePointInstruction)

#endif //CHRYSALIS_FREEPOINTINSTRUCTION_H