#ifndef CHRYSALIS_NAMEMOCK_H
#define CHRYSALIS_NAMEMOCK_H

#include <gmock/gmock.h>

#include "arguments/Argument.h"

namespace Chrysalis {
    class NameMock: public Argument<std::string> {
    public:
        explicit NameMock(const std::string& value): Argument(value){}
        MOCK_METHOD((std::expected<std::string, Error>), get, (), (const, override));
    };
}

#endif //CHRYSALIS_NAMEMOCK_H
