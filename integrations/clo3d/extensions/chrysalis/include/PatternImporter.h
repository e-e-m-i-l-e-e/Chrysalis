#ifndef CHRYSALIS_PATTERNIMPORTER_H
#define CHRYSALIS_PATTERNIMPORTER_H

#include "Project.h"

namespace CLO3D {
    class PatternImporter {
    public:
        explicit PatternImporter(std::unique_ptr<Chrysalis::Project> project);

        void import() const;
    private:
        /// @uml{composition}
        std::unique_ptr<Chrysalis::Project> project_;
    };
}

#endif //CHRYSALIS_PATTERNIMPORTER_H