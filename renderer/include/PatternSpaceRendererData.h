#ifndef CHRYSALIS_PATTERNSPACERENDERERDATA_H
#define CHRYSALIS_PATTERNSPACERENDERERDATA_H

#include <vector>

#include "Point.h"
#include "Vertex3f.h"
#include "BaseRendererData.h"
#include "observers/PatternSpaceObserver.h"

namespace Chrysalis {
    class PatternSpaceRendererData: public BaseRendererData<Vertex3f>, public PatternSpaceObserver {
    public:
        static constexpr float POINT_RADIUS = 0.25f;

        void pointAdded(const Point* point) override;
        void relativePointAdded(const Point* from, const Point* to) override;

        size_t size() override;
        std::vector<Vertex3f> vbo() override;

        size_t linesSize() const;
        size_t arrowsSize() const;
        size_t pointsSize() const;

        bool isPointed(float x, float y) const;
    private:
        std::vector<Vertex3f> lines_;
        std::vector<Vertex3f> arrows_;
        std::vector<Vertex3f> points_;
    };
}

#endif //CHRYSALIS_PATTERNSPACERENDERERDATA_H