#include "instructions/BasePatternInstruction.h"

using namespace Chrysalis;

BasePatternInstruction::BasePatternInstruction(ProjectSpace* space,
                                               SelectedPatternsArgument* selectedPatterns)
    : space_(space), selectedPatterns_(selectedPatterns) {}

BasePatternInstruction::~BasePatternInstruction() {
    delete selectedPatterns_;
}

bool BasePatternInstruction::eachPatternHasPoint(const std::string& point) const {
    std::unordered_set<const Point*> points;
    for (const auto& patternSpace: patterns()) {
        points.insert(patternSpace->getPoint(point));
    }
    return points.size() == 1;
}

const PatternSpace* BasePatternInstruction::anyPattern() const {
    return *patterns().begin();
}
