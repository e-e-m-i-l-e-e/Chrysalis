#include "Project.h"

using namespace PB;

Project::Project(const std::string& name, ProjectParameters* parameters): name_(name), parameters_(parameters) {}

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

std::string Project::getName() {
    return name_;
}

void Project::setName(const std::string& name) {
    name_ = name;
}

ProjectParameters* Project::getParameters() const {
    return parameters_;
}

void Project::addPattern(Pattern* pattern) {
    patterns_.push_front(pattern);
}
