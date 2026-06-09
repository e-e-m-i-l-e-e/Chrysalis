#ifndef CHRYSALIS_PATTERNSPACE_H
#define CHRYSALIS_PATTERNSPACE_H

#include <unordered_map>

#include "Outline.h"
#include "OutlineContainer.h"
#include "ProjectSpace.h"

namespace Chrysalis {
    class SERIALIZABLE(PatternSpace) {
        PROVIDE_SERIALIZATION_ACCESS(PatternSpace)
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
        OutlineContainer* outline_;
        std::unordered_map<std::string, Point*> points_;
    };
    SIMPLE_SERIALIZE_MEMBERS(PatternSpace, outline_)
}

#endif //CHRYSALIS_PATTERNSPACE_H