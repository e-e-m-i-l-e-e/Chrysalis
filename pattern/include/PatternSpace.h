#ifndef CHRYSALIS_PATTERNSPACE_H
#define CHRYSALIS_PATTERNSPACE_H

#include <unordered_map>

#include "Outline.h"
#include "OutlineContainer.h"
#include "ProjectSpace.h"

namespace Chrysalis {
    class PatternSpace {
    public:
        explicit PatternSpace(OutlineContainer* outline);
        ~PatternSpace();

        bool hasPoint(const std::string& name) const;

        Point* getLastPoint() const;
        OutlineContainer* getOutline() const;
        Point* getPoint(const std::string& name) const;
        const std::unordered_map<std::string, Point*>& getPoints() const;

        void addPoint(const std::string& name, Point* point);
    private:
        Point* lastPoint_ = nullptr;
        /// @uml{composition}
        OutlineContainer* outline_ = nullptr;
        std::unordered_map<std::string, Point*> points_;
    };
}

#endif //CHRYSALIS_PATTERNSPACE_H