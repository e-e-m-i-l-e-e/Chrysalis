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
    class SERIALIZABLE(FreePointInstruction): public BasePatternInstruction {
        PROVIDE_SERIALIZATION_ACCESS(FreePointInstruction)
    public:
        explicit FreePointInstruction(ProjectSpace* space, SelectedPatternsArgument* patterns,
                                      const name* pointName, const num* x, const num* y);
        ~FreePointInstruction() override;

        bool isValid() override;
        void execute() override;
    private:
        const name* pointName_;
        const num* x_;
        const num* y_;
    };
    SERIALIZE_DERIVED_MEMBERS(Chrysalis::FreePointInstruction, Chrysalis::BasePatternInstruction, pointName_, x_, y_)
    SERIALIZATION_CONSTRUCTOR(Chrysalis::FreePointInstruction, space_, selectedPatterns_, pointName_, x_, y_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::FreePointInstruction)

#endif //CHRYSALIS_FREEPOINTINSTRUCTION_H