#ifndef FASHIONDESIGNAPPS_PATTERN_H
#define FASHIONDESIGNAPPS_PATTERN_H

#include "Space.h"
#include "DartBuilder.h"
#include "OutlineBuilder.h"

class Pattern {
public:
    explicit Pattern(const std::string& name, Space* space, Outline* outline);
    void addPoint(const std::string& name, double x, double y) const;

    DartBuilder startDart() const;
    OutlineBuilder startOutline() const;

    std::vector<float> getPoints() const;
    std::vector<float> getOutline() const;
private:
    std::string name_;
    Space* space_;
    Outline* outline_;
};

#endif //FASHIONDESIGNAPPS_PATTERN_H