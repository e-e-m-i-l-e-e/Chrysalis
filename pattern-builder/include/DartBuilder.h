#ifndef FASHIONDESIGNAPPS_DARTBUILDER_H
#define FASHIONDESIGNAPPS_DARTBUILDER_H

#include "Dart.h"

class DartBuilder {
public:
    explicit DartBuilder(Dart* dart);

    DartBuilder& addPoint(const std::string& pointName);
private:
    Dart* dart_;
};

#endif //FASHIONDESIGNAPPS_DARTBUILDER_H