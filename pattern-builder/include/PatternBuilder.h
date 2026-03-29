#ifndef CLOEXTENSIONS_PATTERNBUILDER_H
#define CLOEXTENSIONS_PATTERNBUILDER_H

#include "Extension.h"


class PatternBuilder: public Extension {
protected:
    ~PatternBuilder() override = default;

public:
    void configureStatusBar(QWidget *parent) override;
};


#endif //CLOEXTENSIONS_PATTERNBUILDER_H