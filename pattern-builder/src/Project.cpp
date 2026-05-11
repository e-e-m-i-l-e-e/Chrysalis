#include "Project.h"

Project::~Project() {
    for (const auto pattern: patterns_) {
        delete pattern;
    }
}

Pattern* Project::addPattern(const std::string &name) {
    const auto space = new Space();
    const auto outline = new Outline(space);
    const auto pattern = new Pattern(name, space, outline);
    patterns_.push_front(pattern);
    return pattern;
}