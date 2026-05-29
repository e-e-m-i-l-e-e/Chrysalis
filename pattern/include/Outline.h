#ifndef CHRYSALIS_OUTLINE_H
#define CHRYSALIS_OUTLINE_H

#include <forward_list>

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polygon_with_holes_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>

#include "Dart.h"
#include "Space.h"

namespace Chrysalis {
    class Outline {
        using Polygon_with_holes = CGAL::Polygon_with_holes_2<Kernel>;
        using Vb  = CGAL::Triangulation_vertex_base_2<Kernel>;
        using CFb = CGAL::Constrained_triangulation_face_base_2<Kernel>;
        using Fb  = CGAL::Triangulation_face_base_with_info_2<int, Kernel, CFb>;
        using TDS = CGAL::Triangulation_data_structure_2<Vb, Fb>;
        using Triangulation = CGAL::Constrained_Delaunay_triangulation_2<Kernel, TDS>;
    public:
        explicit Outline(Space* space);
        ~Outline();

        void addPoint(const std::string& pointName);
        void addDart(Dart* dart);

        std::vector<std::vector<float>> getPoints() const;
        std::vector<float> getShape() const;
    private:
        Space* space_;
        Polygon_with_holes polygon_;
        std::forward_list<Dart*> darts_;
    };
}

#endif //CHRYSALIS_OUTLINE_H