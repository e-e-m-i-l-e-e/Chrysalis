#ifndef FASHIONDESIGNAPPS_SPACE_H
#define FASHIONDESIGNAPPS_SPACE_H

#include <unordered_map>

#include <CGAL/Simple_cartesian.h>

#include "SpaceRendererData.h"
#include "SpaceVertex.h"

using Kernel = CGAL::Simple_cartesian<double>;
using Point = Kernel::Point_2;
using Vector = Kernel::Vector_2;

class Space {
public:
    explicit Space(const SpaceRendererData* rendererData);
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

    std::vector<SpaceVertex> getVBO() const;
    int getNumberOfPoints() const;
    // std::vector<DistancedVertex> getDistancedVBO() const;
private:
    const SpaceRendererData* rendererData_;
    std::list<std::string> insertionOrder_;
    std::unordered_map<std::string, Point> points_;
    std::unordered_map<std::string, std::string> parentPoints_;
};

#endif //FASHIONDESIGNAPPS_SPACE_H