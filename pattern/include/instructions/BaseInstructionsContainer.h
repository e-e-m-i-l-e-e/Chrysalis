#ifndef CHRYSALIS_BASEINSTRUCTIONSCONTAINER_H
#define CHRYSALIS_BASEINSTRUCTIONSCONTAINER_H

#include <thread>

#include "Option.h"
#include "Expression.h"
#include "BaseInstruction.h"
#include "CompositiveContainer.h"

/** @defgroup Instructions Instructions
 *  @{
 */
namespace Chrysalis {
    template<typename T>
    requires std::derived_from<T, BaseInstruction>
    class BaseInstructionsContainer: public BaseInstruction {
        PROVIDE_DEFAULT_SERIALIZATION_ACCESS(BaseInstructionsContainer)
        SERIALIZE_DERIVED_FROM(BaseInstruction, options_, expressions_, instructions_);
    public:
        explicit BaseInstructionsContainer(OptionsContainer* options, ExpressionsContainer* expressions)
            : options_(options), expressions_(expressions) {}
        ~BaseInstructionsContainer() override {
            delete options_;
            delete expressions_;
            for (const auto& instruction: instructions_) delete instruction;
        }
        void ignore() override {
            for (const auto& instruction: instructions_) {
                instruction->ignore();
            }
        }
        void add(T* instruction) {
            lastInstruction_ = instructions_.insert(
                lastInstruction_ == instructions_.end() ? instructions_.end() : std::next(lastInstruction_),
                instruction
            );
            // (*lastInstruction_)->run();
        }
        std::list<T*>::const_iterator begin() const {
            return instructions_.begin();
        }
        std::list<T*>::const_iterator end() const {
            return instructions_.end();
        }
        [[nodiscard]] OptionsContainer* options() const {
            return options_;
        }
        [[nodiscard]] ExpressionsContainer* expressions() const {
            return expressions_;
        }
    protected:
        void execute() override {
            for (auto it = instructions_.begin(); it != instructions_.end(); ++it) {
                (*it)->run();
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                lastInstruction_ = it;
            }
        }
    private:
        /// @uml{composition}
        OptionsContainer* options_;
        /// @uml{composition}
        ExpressionsContainer* expressions_;
        /// @uml{composition}
        std::list<T*> instructions_;
        std::list<T*>::iterator lastInstruction_ = instructions_.end();
    };
    using InstructionsContainer = BaseInstructionsContainer<BaseInstruction>;
}
/**@}*/

#endif //CHRYSALIS_BASEINSTRUCTIONSCONTAINER_H