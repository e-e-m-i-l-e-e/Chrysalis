#ifndef FASHIONDESIGNAPPS_PATTERNBUILDER_H
#define FASHIONDESIGNAPPS_PATTERNBUILDER_H

#include "Pattern.h"

class PatternBuilder {
public:
    enum Direction {
        RIGHT,
        LEFT,
        UP,
        DOWN
    };
    explicit PatternBuilder(Pattern* pattern);

    PatternBuilder& addPoint(const std::string& name, double x, double y);
    PatternBuilder& addPoint(const std::string& fromPointName, const std::string& name, double angle, double length);
    PatternBuilder& addPoint(const std::string& fromPointName, const std::string& name, Direction direction, double length);
    // Start from last added point
    PatternBuilder& nextPoint(const std::string& name, double angle, double length);
    PatternBuilder& nextPoint(const std::string& name, Direction direction, double length);

    OutlineBuilder editOutline() const;
private:
    Pattern* pattern_;
};

#endif //FASHIONDESIGNAPPS_PATTERNBUILDER_H