#include "Project.h"

using namespace PB;

Project::Project(ProjectParameters* parameters): parameters_(parameters) {}

Project::~Project() {
    delete parameters_;
    for (const auto pattern: patterns_) {
        delete pattern;
    }
}

Project* Project::create() {
    auto* parameters = new ProjectParameters();
    return new Project(parameters);
}

void Project::addPattern(Pattern* pattern) {
    patterns_.push_front(pattern);
}
