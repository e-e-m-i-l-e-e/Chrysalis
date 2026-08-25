#ifndef CHRYSALIS_INSTRUCTIONSCONTAINERMOCK_H
#define CHRYSALIS_INSTRUCTIONSCONTAINERMOCK_H

#include <gmock/gmock.h>

#include "OptionsContainerMock.h"
#include "ExpressionsContainerMock.h"
#include "instructions/BaseInstructionsContainer.h"

namespace Chrysalis {
    class InstructionsContainerMock : public InstructionsContainer {
    public:
        explicit InstructionsContainerMock()
            : InstructionsContainer(new OptionsContainerMock(), new ExpressionsContainerMock()) {}
        MOCK_METHOD(void, ignore, (), (override));
        MOCK_METHOD(void, execute, (), (override));
    };
}

#endif // CHRYSALIS_INSTRUCTIONSCONTAINERMOCK_H
