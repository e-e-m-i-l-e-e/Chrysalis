#ifndef FASHIONDESIGNAPPS_OUTLINE_H
#define FASHIONDESIGNAPPS_OUTLINE_H

#include <forward_list>

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polygon_with_holes_2.h>

#include "Dart.h"
#include "Space.h"

class Outline {
    using Polygon_with_holes = CGAL::Polygon_with_holes_2<Kernel>;
public:
    explicit Outline(Space* space);
    ~Outline();

    void addPoint(const std::string& pointName);
    void addDart(Dart* dart);

    std::vector<float> getPoints() const;
private:
    Space* space_;
    Polygon_with_holes polygon_;
    std::forward_list<Dart*> darts_;
};


#endif //FASHIONDESIGNAPPS_OUTLINE_H