#include "Outline.h"

#include <queue>

using namespace PB;

Outline::Outline(Space* space): space_(space) {}

Outline::~Outline() {
    for (const auto dart: darts_) {
        delete dart;
    }
}

void Outline::addPoint(const std::string& pointName) {
    polygon_.outer_boundary().push_back(space_->getPoint(pointName));
}

void Outline::addDart(Dart* dart) {
    darts_.push_front(dart);
    polygon_.add_hole(dart->getPolygon());
}

std::vector<std::vector<float>> Outline::getPoints() const {
    int i = 0;
    std::vector<std::vector<float>> points(polygon_.holes().size() + 1);
    std::vector<float> outlinePoints(polygon_.outer_boundary().size() * 2);
    for (const auto& point: polygon_.outer_boundary()) {
        outlinePoints[i] = point.x();
        outlinePoints[i + 1] = point.y();
        i += 2;
    }
    i = 0;
    points[i++] = outlinePoints;
    for (const auto& dart: darts_) {
        points[i++] = dart->getPoints();
    }
    return points;
}

std::vector<float> Outline::getShape() const {
    Triangulation triangulation;

    // Insert outer boundary
    triangulation.insert_constraint(
        polygon_.outer_boundary().vertices_begin(),
        polygon_.outer_boundary().vertices_end(),
        true
    );

    // Insert holes (if any)
    for (auto& hole : polygon_.holes()) {
        triangulation.insert_constraint(
            hole.vertices_begin(),
            hole.vertices_end(),
            true
        );
    }

    // Mark all faces as unvisited (-1), outside (0), inside (1)
    for (auto f = triangulation.all_faces_begin(); f != triangulation.all_faces_end(); ++f) {
        f->info() = -1;
    }

    // Flood-fill from infinite face (which is always outside = 0)
    std::queue<Triangulation::Face_handle> queue;
    triangulation.infinite_face()->info() = 0;
    queue.push(triangulation.infinite_face());

    while (!queue.empty()) {
        auto face = queue.front();
        queue.pop();

        for (int i = 0; i < 3; ++i) {
            auto neighbor = face->neighbor(i);

            if (neighbor->info() != -1)  // already visited
                continue;

            if (triangulation.is_constrained({face, i}))
                neighbor->info() = 1 - face->info();  // flip across boundary
            else
                neighbor->info() = face->info();       // same region

            queue.push(neighbor);
        }
    }

    // Collect triangles inside the polygon
    std::vector<float> vertices;
    for (auto f = triangulation.finite_faces_begin(); f != triangulation.finite_faces_end(); ++f) {
        if (f->info() != 1) continue;  // skip outside and unvisited

        for (int i = 0; i < 3; ++i) {
            auto p = f->vertex(i)->point();
            vertices.push_back(static_cast<float>(p.x()));
            vertices.push_back(static_cast<float>(p.y()));
        }
    }

    return vertices;
}
