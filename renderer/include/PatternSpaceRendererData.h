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
        void pointAdded(const Point* point) override;
        void relativePointAdded(const Point* from, const Point* to) override;

        size_t count() override;
        std::vector<Vertex3f> vbo() override;

        size_t linesCount() const;
        size_t pointsCount() const;
    private:
        std::vector<Vertex3f> lines_;
        std::vector<Vertex3f> points_;
    };
}

#endif //CHRYSALIS_PATTERNSPACERENDERERDATA_H