#include "Project.h"

using namespace PB;

Project::Project(const std::string& name, ProjectParameters* parameters): name(name), parameters_(parameters) {}

Project::~Project() {
    delete parameters_;
    for (const auto pattern: patterns_) {
        delete pattern;
    }
}

Project* Project::create() {
    auto* parameters = new ProjectParameters();
    return new Project("Untitled", parameters);
}

void Project::addPattern(Pattern* pattern) {
    patterns_.push_front(pattern);
}
