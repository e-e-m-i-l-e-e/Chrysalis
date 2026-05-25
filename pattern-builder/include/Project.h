#ifndef FASHIONDESIGNAPPS_PROJECT_H
#define FASHIONDESIGNAPPS_PROJECT_H

#include <forward_list>

#include "PatternBuilder.h"
#include "ProjectParameters.h"

namespace PB
{
    class Project;
}

namespace boost::serialization {
    template<class Archive>
    void save_construct_data(Archive&, const PB::Project*, const unsigned int);

    template<class Archive>
    void load_construct_data(Archive&, PB::Project*, const unsigned int);
}

namespace PB {
    class Project {
        friend class boost::serialization::access;
    public:
        explicit Project(const std::string& name, ProjectParameters* parameters);
        ~Project();

        static Project* create();

        void addPattern(Pattern* pattern);

        std::string name;
    private:

        ProjectParameters* parameters_;
        std::forward_list<Pattern*> patterns_;

        template<class Archive>
        void serialize(Archive& archive, const unsigned int version) {
            archive & name;
            archive & parameters_;
        }
        template<class Archive>
        friend void boost::serialization::save_construct_data(Archive&, const Project*, const unsigned int);

        template<class Archive>
        friend void boost::serialization::load_construct_data(Archive&, Project*, const unsigned int);
    };
}

#endif //FASHIONDESIGNAPPS_PROJECT_H