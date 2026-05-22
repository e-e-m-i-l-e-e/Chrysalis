#ifndef FASHIONDESIGNAPPS_PROJECT_H
#define FASHIONDESIGNAPPS_PROJECT_H

#include <forward_list>

#include "PatternBuilder.h"
#include "ProjectParameters.h"

namespace PB {
    class Project {
    public:
        explicit Project(ProjectParameters* parameters);
        ~Project();

        void addPattern(Pattern* pattern);
    private:
        ProjectParameters* parameters_;
        std::forward_list<Pattern*> patterns_;
    };
}

#endif //FASHIONDESIGNAPPS_PROJECT_H