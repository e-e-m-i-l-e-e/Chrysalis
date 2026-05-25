#ifndef FASHIONDESIGNAPPS_PROJECT_H
#define FASHIONDESIGNAPPS_PROJECT_H

#include <forward_list>

#include "PatternBuilder.h"
#include "ProjectParameters.h"

namespace PB {
    class Project {
        friend class boost::serialization::access;
    public:
        explicit Project(ProjectParameters* parameters);
        ~Project();

        static Project* create();

        void addPattern(Pattern* pattern);
    private:
        ProjectParameters* parameters_;
        std::forward_list<Pattern*> patterns_;

        template<class Archive>
        void serialize(Archive& archive, const unsigned int version) {
            archive & parameters_;
        }
    };
}

#endif //FASHIONDESIGNAPPS_PROJECT_H