#ifndef FASHIONDESIGNAPPS_ARCHIVE_H
#define FASHIONDESIGNAPPS_ARCHIVE_H

#include "Project.h"

namespace Chrysalis::Pattern {
    class Archive {
    public:
        PB::Project* read(const char* filePath);
        void write(const char* filePath, PB::Project* project);
    };
}

// Constructors
namespace boost::serialization {
    template<class Archive>
    void save_construct_data(Archive& archive, const PB::Project& project, const unsigned int version) {
        archive & project.parameters_;
    }

    template<class Archive>
    void load_construct_data(Archive& archive, PB::Project* project, const unsigned int version) {
        ProjectParameters* parameters;
        archive >> parameters;
        ::new(project) PB::Project(parameters);
    }

    template<class Archive>
    void save_construct_data(Archive& archive, const Parameter& parameter, const unsigned int version) {
        archive & parameter.name_;
        archive & parameter.value_;
    }

    template<class Archive>
    void load_construct_data(Archive &archive, Parameter* parameter, const unsigned int version) {
        double value_;
        std::string name_;

        archive >> name_;
        archive >> value_;

        ::new(parameter) Parameter(name_, value_);
    }
}

#endif //FASHIONDESIGNAPPS_ARCHIVE_H