#ifndef CHRYSALIS_PATTERNSPACERENDERERDATA_H
#define CHRYSALIS_PATTERNSPACERENDERERDATA_H

#include <vector>

#include "Point.h"
#include "Vertex3f.h"
#include "BaseRendererData.h"
#include "observers/PatternSpaceObserver.h"

namespace Chrysalis {
    class PatternSpaceRendererData: public BaseRendererData<Vertex3f>, public PatternSpaceObserver, public PointObserver {
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
        void relativePointConnectionAdded(const Point* from, const Point* to) override;
        void relativePointConnectionRemoved(const Point* from, const Point* to) override;

        size_t size() override;
        std::vector<Vertex3f> vbo() override;

        size_t linesSize() const;
        size_t arrowsSize() const;
        size_t pointsSize() const;

        const Point* pointAtPosition(float x, float y) const;
    private:
        static float length(const CG::Point& pointFrom, const CG::Point& pointTo);
        static Arrow buildArrow(const CG::Point& pointFrom, const CG::Point& pointTo);
        static CG::Point intersectionPoint(const CG::Point& pointFrom, const CG::Point& pointTo);

        std::vector<Vertex3f> lines_;
        std::vector<Vertex3f> arrows_;
        std::vector<Vertex3f> points_;

        std::unordered_map<const Point*, int> pointIndices_;
        std::unordered_map<const Point*, std::unordered_map<const Point*, int>> connectionsMapFrom_; // <from, <to, line index>>
        std::unordered_map<const Point*, std::unordered_map<const Point*, int>> connectionsMapTo_; // <to, <from, line index>>
    };
}

#endif //CHRYSALIS_PATTERNSPACERENDERERDATA_H