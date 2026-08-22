#ifndef CHRYSALIS_PATTERNSHAPERENDERERDATA_H
#define CHRYSALIS_PATTERNSHAPERENDERERDATA_H

#include <unordered_map>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>

#include "CGAL.h"
#include "Layout.h"
#include "BaseRendererData.h"
#include "BaseObservableRendererData.h"
#include "PatternSpace.h"
#include "observers/PatternShapeObserver.h"

namespace Chrysalis {
    class PatternShapeRendererData: public BaseObservableRendererData<Vertex2f>, public PatternShapeObserver {
    public:
        explicit PatternShapeRendererData(BaseObservable<PatternShapeObserver>* observable,
                                          const std::vector<BaseRendererObserver*>& observers);
        ~PatternShapeRendererData() override;

        void pointAdded(const Outline* outline, const Point* point) override;

        [[nodiscard]] std::vector<Layout> layout() const;
        std::vector<Vertex2f> vbo() override;
        size_t size() override;
    private:
        BaseObservable<PatternShapeObserver>* observable_;
        std::unordered_map<const Outline*, std::vector<Vertex2f>> data_;
        std::unordered_map<const Outline*, CGAL::Constrained_Delaunay_triangulation_2<CG::LinearKernel>> triangulation_;
    };
}

#endif //CHRYSALIS_PATTERNSHAPERENDERERDATA_H