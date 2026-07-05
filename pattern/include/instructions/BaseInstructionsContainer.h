#ifndef CHRYSALIS_BASEINSTRUCTIONSCONTAINER_H
#define CHRYSALIS_BASEINSTRUCTIONSCONTAINER_H

#include "BaseInstruction.h"
#include "CompositiveContainer.h"

namespace Chrysalis {
    template<typename T>
    requires std::derived_from<T, BaseInstruction>
    class BaseInstructionsContainer: public BaseInstruction, public CompositiveContainer<T> {
        friend boost::serialization::access;

        template <class Archive>
        void serialize(Archive& archive, const unsigned int)
        {
            archive & boost::serialization::base_object<BaseInstruction>(*this);
            archive & boost::serialization::base_object<CompositiveContainer<T>>(*this);
        }
    public:
        bool isValid() override {
            return true;
        }
        void execute() override {
            for (const auto& instruction: *this) {
                instruction->execute();
            }
        }
    };
}

#endif //CHRYSALIS_BASEINSTRUCTIONSCONTAINER_H