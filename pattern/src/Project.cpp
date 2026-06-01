#include "Project.h"

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

using namespace Chrysalis;

Project::Project(std::string name, ProjectSpace* space, Parameters* parameters, InstructionsContainer* instructions)
    : name_(std::move(name)), space_(space), parameters_(parameters), instructions_(instructions) {}

Project::~Project() {
    delete space_;
    delete parameters_;
    delete instructions_;
    for (const auto pattern: patterns_) {
        delete pattern;
    }
}

Project* Project::create() {
    return new Project("Untitled", new ProjectSpace(), new Parameters(), new InstructionsContainer());
}

Project* Project::read(const std::string& filePath) {
    try {
        std::ifstream file(filePath, std::ios::binary);
        if (!file.is_open()) {
            std::cout << "Failed to open file: " << filePath;
            return nullptr;
        }

        boost::archive::binary_iarchive archive(file);
        Project* project;
        archive >> project;
        return project;
    } catch (const boost::archive::archive_exception &e) {
        std::cout << "Archive error: " << e.what();
    } catch (const std::exception &e) {
        std::cout << "Read error: " << e.what();
    }
    return nullptr;
}

void Project::write(const std::string& filePath, Project* project) {
    try {
        std::ofstream file(filePath, std::ios::binary);
        if (!file.is_open()) {
            std::cout << "Failed to open file: " << filePath;
            return;
        }

        boost::archive::binary_oarchive archive(file);
        archive << project;

        file.flush();
        file.close();
    } catch (const boost::archive::archive_exception &e) {
        std::cout << "Archive error: " << e.what();
    } catch (const std::exception &e) {
        std::cout << "Write error: " << e.what();
    }
}

std::string Project::getName() {
    return name_;
}

void Project::setName(const std::string& name) {
    name_ = name;
}

Parameters* Project::getParameters() const {
    return parameters_;
}

void Project::addPattern(Pattern* pattern) {
    patterns_.push_front(pattern);
}
