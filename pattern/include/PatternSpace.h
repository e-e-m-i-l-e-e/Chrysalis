#ifndef CHRYSALIS_PATTERNSPACE_H
#define CHRYSALIS_PATTERNSPACE_H

#include <unordered_map>

#include "Space.h"

class PatternSpace {
public:
    explicit PatternSpace(Space* space);

    bool hasPoint(const std::string& name) const;
    Point* getPoint(const std::string& name) const;
    void addPoint(const std::string& name, Point* point);
private:
    Space* space_;
    std::unordered_map<std::string, Point*> points_;
};

#endif //CHRYSALIS_PATTERNSPACE_H