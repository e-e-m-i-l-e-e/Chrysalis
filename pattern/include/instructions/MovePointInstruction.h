#ifndef CHRYSALIS_MOVEPOINTINSTRUCTION_H
#define CHRYSALIS_MOVEPOINTINSTRUCTION_H

#include <boost/serialization/export.hpp>

#include "BasePatternInstruction.h"

namespace Chrysalis {
    class SERIALIZABLE(MovePointInstruction): public BasePatternInstruction {
        PROVIDE_SERIALIZATION_ACCESS(MovePointInstruction)
    public:
        explicit MovePointInstruction(ProjectSpace* space, SelectedPatternsArgument* patterns, const name* pointName,
                                      const num* angle, const num* length);
        ~MovePointInstruction() override = default;

        bool isValid() override;
        void execute() override;
    private:
        const name* pointName_;
        const num* angle_;
        const num* length_;
    };
    SERIALIZE_DERIVED_MEMBERS(MovePointInstruction, BasePatternInstruction, pointName_, angle_, length_)
    SERIALIZATION_CONSTRUCTOR(MovePointInstruction, space_, selectedPatterns_, pointName_, angle_, length_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::MovePointInstruction)

#endif //CHRYSALIS_MOVEPOINTINSTRUCTION_H