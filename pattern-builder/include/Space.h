#ifndef FASHIONDESIGNAPPS_SPACE_H
#define FASHIONDESIGNAPPS_SPACE_H

#include <unordered_map>

#include "SpaceRendererData.h"

class Space {
public:
    explicit Space(SpaceRendererData* rendererData);
    ~Space();

    enum Direction {
        RIGHT,
        LEFT,
        UP,
        DOWN
    };
    void addPoint(const std::string& name, double x, double y);
    void addPoint(const std::string& fromPointName, const std::string& name, double angle, double length);
    void addPoint(const std::string& fromPointName, const std::string& name, Direction direction, double length);
    // Start from last added point
    void nextPoint(const std::string& name, double angle, double length);
    void nextPoint(const std::string& name, Direction direction, double length);

    double distance(const std::string& from, const std::string& to) const;
    Point& getPoint(const std::string& name);

    const SpaceRendererData* getRendererData() const;
private:
    void addPoint(const std::string& name, const Point& point);

    SpaceRendererData* rendererData_;

    std::string lastPointName_;
    std::set<std::string> tailPoints_;
    std::unordered_map<std::string, Point> points_;
    std::unordered_map<std::string, int> linesIndices_;
    std::unordered_map<std::string, std::string> parentPoints_;
};

#endif //FASHIONDESIGNAPPS_SPACE_H