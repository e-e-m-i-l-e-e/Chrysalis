#include "Project.h"

using namespace PB;

Project::Project(ProjectParameters* parameters): parameters_(parameters) {}

Project::~Project() {
    delete parameters_;
    for (const auto pattern: patterns_) {
        delete pattern;
    }
}

PatternBuilder Project::addPattern(const std::string &name) {
    const auto spaceRendererData = new SpaceRendererData();
    const auto space = new Space(spaceRendererData);
    const auto outline = new Outline(space);
    const auto pattern = new Pattern(name, space, outline);
    patterns_.push_front(pattern);
    return PatternBuilder(space, pattern);
}