#ifndef CHRYSALIS_MOVEPOINTINSTRUCTION_H
#define CHRYSALIS_MOVEPOINTINSTRUCTION_H

#include <boost/serialization/export.hpp>

#include "BasePatternInstruction.h"

namespace Chrysalis {
    class SERIALIZABLE(MovePointInstruction): public BasePatternInstruction {
        PROVIDE_SERIALIZATION_ACCESS(MovePointInstruction)
    public:
        explicit MovePointInstruction(ProjectSpace* space, args::patterns* patterns, const args::name* pointName,
                                      const args::number* angle, const args::number* length);
        ~MovePointInstruction() override = default;

        bool isValid() override;
        void execute() override;
    private:
        const args::name* pointName_;
        const args::number* angle_;
        const args::number* length_;
    };
    SIMPLE_SERIALIZE_DERIVED_MEMBERS(MovePointInstruction, BasePatternInstruction, space_, patterns_, pointName_, angle_, length_)
}

BOOST_CLASS_EXPORT_KEY(Chrysalis::MovePointInstruction)

#endif //CHRYSALIS_MOVEPOINTINSTRUCTION_H