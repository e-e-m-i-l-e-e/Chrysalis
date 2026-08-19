#ifndef CHRYSALIS_PROJECTREADERROR_H
#define CHRYSALIS_PROJECTREADERROR_H

#include <stdexcept>

namespace Chrysalis {
    class ProjectIOError: public std::runtime_error {
    public:
        explicit ProjectIOError(const std::string& filePath);
    };
}

#endif // CHRYSALIS_PROJECTREADERROR_H
