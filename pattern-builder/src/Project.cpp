#include "Project.h"

Project::~Project() {
    for (const auto pattern: patterns_) {
        delete pattern;
    }
}

Pattern* Project::createPattern(const std::string &name) {
    patterns_.push_front(new Pattern(name));
    return patterns_.front();
}