#ifndef FASHIONDESIGNAPPS_DARTBUILDER_H
#define FASHIONDESIGNAPPS_DARTBUILDER_H

#include "Dart.h"
#include "Outline.h"

namespace PB {
    class DartBuilder {
    public:
        explicit DartBuilder(Outline* outline, Dart* dart);

        DartBuilder& addPoint(const std::string& pointName);
        void complete() const;
    private:
        Dart* dart_;
        Outline* outline_;
    };
}

#endif //FASHIONDESIGNAPPS_DARTBUILDER_H