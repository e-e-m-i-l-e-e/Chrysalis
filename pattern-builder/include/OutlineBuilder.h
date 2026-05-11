#ifndef FASHIONDESIGNAPPS_OUTLINEBUILDER_H
#define FASHIONDESIGNAPPS_OUTLINEBUILDER_H

#include "Outline.h"

class OutlineBuilder {
public:
    explicit OutlineBuilder(Outline* outline);

    OutlineBuilder& addPoint(const std::string& pointName);
private:
    Outline* outline_;
};

#endif //FASHIONDESIGNAPPS_OUTLINEBUILDER_H