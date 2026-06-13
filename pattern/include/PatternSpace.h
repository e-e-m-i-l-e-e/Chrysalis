#ifndef CHRYSALIS_PATTERNSPACE_H
#define CHRYSALIS_PATTERNSPACE_H

#include <unordered_map>

#include "Outline.h"
#include "OutlineContainer.h"
#include "ProjectSpace.h"
#include "observers/BaseObservable.h"
#include "observers/PatternSpaceObserver.h"

namespace Chrysalis {
    class SERIALIZABLE(PatternSpace): public BaseObservable<PatternSpaceObserver> {
        PROVIDE_SERIALIZATION_ACCESS(PatternSpace)
    public:
        explicit PatternSpace(OutlineContainer* outline);
        ~PatternSpace();

        [[nodiscard]] bool hasPoint(const std::string& name) const;

        [[nodiscard]] Point* getLastPoint() const;
        [[nodiscard]] OutlineContainer* getOutline() const;
        [[nodiscard]] const Point* getPoint(const std::string& name) const;
        [[nodiscard]] const std::unordered_map<std::string, Point*>& getPoints() const;

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