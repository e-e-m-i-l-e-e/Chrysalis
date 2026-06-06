#ifndef CHRYSALIS_PATTERNIMPORTER_H
#define CHRYSALIS_PATTERNIMPORTER_H

#include "Project.h"

namespace Chrysalis {
    class PatternImporter {
    public:
        explicit PatternImporter(Project* project);

        void import() const;
    private:
        /// @uml{composition}
        Project* project_;
    };
}

#endif //CHRYSALIS_PATTERNIMPORTER_H