#ifndef CHRYSALIS_ARCHIVE_H
#define CHRYSALIS_ARCHIVE_H

#include <boost/serialization/unordered_map.hpp>

#include "Project.h"

namespace Chrysalis {
    class Archive {
    public:
        Project* read(const char* filePath);
        void write(const char* filePath, Project* project);
    };
}

#endif //CHRYSALIS_ARCHIVE_H