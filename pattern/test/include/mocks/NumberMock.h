#ifndef CHRYSALIS_NUMBERMOCK_H
#define CHRYSALIS_NUMBERMOCK_H

#include <gmock/gmock.h>

#include "arguments/BaseArgument.h"

namespace Chrysalis {
    class NumberMock: public BaseArgument<double> {
    public:
        MOCK_METHOD((std::expected<double, Error>), get, (), (const, override));
    };
}

#endif //CHRYSALIS_NUMBERMOCK_H
