#ifndef CHRYSALIS_ERROR_H
#define CHRYSALIS_ERROR_H

#include <string>

namespace Chrysalis {
    class Error {
    public:
        explicit Error(const std::string& message);

        std::string_view message() const;
    private:
        std::string message_;
    };
}

#endif //CHRYSALIS_ERROR_H
