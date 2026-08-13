#ifndef CHRYSALIS_PATTERNSPACERENDERERDATA_H
#define CHRYSALIS_PATTERNSPACERENDERERDATA_H

#include <vector>

#include "Point.h"
#include "Layout.h"
#include "Vertex3f.h"
#include "BaseRendererData.h"
#include "observers/PatternTraceObserver.h"

namespace Chrysalis {
    class PatternTraceRendererData: public BaseRendererData<Vertex3f>, public PatternTraceObserver, public PointObserver {
        struct Arrow {
            CG::Point baseBegin;
            CG::Point baseEnd;
            CG::Point leftWing;
            CG::Point rightWing;
        };
    public:
        static constexpr float POINT_RADIUS = 0.25f;

        void pointMoved(const Point* point) override;
        void pointAdded(const Point* point) override;
        void curveAdded(const Curve* curve) override;
        void transformed(const Transformation& transformation) override;
        void relativePointConnectionAdded(const Point* from, const Point* to) override;
        void relativePointConnectionRemoved(const Point* from, const Point* to) override;

        size_t size() override;
        std::vector<Vertex3f> vbo() override;

        [[nodiscard]] Layout pointsLayout() const;
        [[nodiscard]] std::vector<Layout> linesLayout() const;
        [[nodiscard]] std::vector<Layout> arrowsLayout() const;

        [[nodiscard]] const Point* pointAtPosition(float x, float y) const;
    private:
        static float length(const CG::Point& pointFrom, const CG::Point& pointTo);
        static Arrow buildArrow(const CG::Point& pointFrom, const CG::Point& pointTo);
        static CG::Point intersectionPoint(const CG::Point& pointFrom, const CG::Point& pointTo);

        std::vector<Vertex3f> points_;
        std::vector<Vertex3f> arrows_;
        std::vector<std::vector<Vertex3f>> lines_;

        std::unordered_map<const Point*, int> pointIndices_;
        std::unordered_map<const Point*, std::unordered_map<const Point*, int>> connectionsMapFrom_; // <from, <to, line index>>
        std::unordered_map<const Point*, std::unordered_map<const Point*, int>> connectionsMapTo_; // <to, <from, line index>>
    };
}

#endif //CHRYSALIS_PATTERNSPACERENDERERDATA_H