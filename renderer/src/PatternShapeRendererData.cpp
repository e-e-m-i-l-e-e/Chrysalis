#include "PatternShapeRendererData.h"

#include <ranges>

using namespace Chrysalis;

PatternShapeRendererData::PatternShapeRendererData(BaseObservable<PatternShapeObserver>* observable,
                                                   const std::vector<BaseRendererObserver*>& observers)
    : BaseObservableRendererData(observers), observable_(observable) {
    observable_->addObserver(this);
}

PatternShapeRendererData::~PatternShapeRendererData() {
    observable_->removeObserver(this);
}

void PatternShapeRendererData::pointAdded(const Outline* outline, const Point* point) {
    if (!data_.contains(outline)) {
        triangulation_.emplace(outline, CGAL::Constrained_Delaunay_triangulation_2<CG::LinearKernel>{});
        data_.emplace(outline, std::vector<Vertex2f>());
    }
    data_[outline].clear();
    triangulation_[outline].insert(*point);
    for (auto face = triangulation_[outline].finite_faces_begin();
         face != triangulation_[outline].finite_faces_end(); ++face) {
        data_[outline].emplace_back(face->vertex(0)->point());
        data_[outline].emplace_back(face->vertex(1)->point());
        data_[outline].emplace_back(face->vertex(2)->point());
    }
    updateVBO();
}

std::vector<Layout> PatternShapeRendererData::layout() const {
    std::vector<Layout> layouts;
    for (const auto& outline: data_ | std::views::values) {
        layouts.emplace_back(0, outline.size());
    }
    return layouts;
}

std::vector<Vertex2f> PatternShapeRendererData::vbo() {
    std::vector<Vertex2f> vbo;
    for (const auto& triangles : data_ | std::views::values) {
        vbo.insert(vbo.end(), triangles.cbegin(), triangles.cend());
    }
    return vbo;
}

size_t PatternShapeRendererData::size() {
    return std::accumulate(data_.begin(), data_.end(), static_cast<size_t>(0), [](auto sum, auto data) {
        return sum + data.second.size();
    });
}