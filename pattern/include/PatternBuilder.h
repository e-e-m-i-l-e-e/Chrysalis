#ifndef FASHIONDESIGNAPPS_PATTERNBUILDER_H
#define FASHIONDESIGNAPPS_PATTERNBUILDER_H

#include "Pattern.h"
#include "Vertex.h"

namespace PB {
    class PatternBuilder {
    public:
        explicit PatternBuilder(Space* space, Pattern* pattern);

        PatternBuilder& addPoint(const std::string& name, double x, double y);
        PatternBuilder& addPoint(const std::string& fromPointName, const std::string& name, double angle, double length);
        PatternBuilder& addPoint(const std::string& fromPointName, const std::string& name, Space::Direction direction, double length);
        // Start from last added point
        PatternBuilder& nextPoint(const std::string& name, double angle, double length);
        PatternBuilder& nextPoint(const std::string& name, Space::Direction direction, double length);

        OutlineBuilder editOutline() const;
        // TEMP
        // std::vector<int> getEBO() const;
        Space& getSpace() const;

        const SpaceRendererData* getSpaceRendererData() const;
        // std::vector<DistancedVertex> getDistancedVBO() const;
    private:
        Space* space_;
        Pattern* pattern_;
    };
}

#endif //FASHIONDESIGNAPPS_PATTERNBUILDER_H