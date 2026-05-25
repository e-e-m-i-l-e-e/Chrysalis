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
    void save_construct_data(Archive& archive, const PB::Project* project, const unsigned int version) {
        archive & project->name;
        archive & project->parameters_;
    }

    template<class Archive>
    void load_construct_data(Archive& archive, PB::Project* project, const unsigned int version) {
        std::string name;
        ProjectParameters* parameters;
        archive >> name;
        archive >> parameters;
        ::new(project) PB::Project(name, parameters);
    }

    template<class Archive>
    void save_construct_data(Archive& archive, const Parameter* parameter, const unsigned int version) {
        archive << parameter->name_;
        archive << parameter->value_;
    }

    template<class Archive>
    void load_construct_data(Archive& archive, Parameter* parameter, const unsigned int version) {
        std::string name;
        double value;
        archive >> name;
        archive >> value;
        ::new(parameter) Parameter(name, value);
    }
}

#endif //FASHIONDESIGNAPPS_ARCHIVE_H