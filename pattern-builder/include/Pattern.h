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
    OutlineBuilder editOutline() const;

    std::vector<float> getPoints() const;
    std::vector<std::vector<float>> getOutline() const;
    std::vector<float> getShape() const;
private:
    std::string name_;
    Space* space_;
    Outline* outline_;
};

#endif //FASHIONDESIGNAPPS_PATTERN_H