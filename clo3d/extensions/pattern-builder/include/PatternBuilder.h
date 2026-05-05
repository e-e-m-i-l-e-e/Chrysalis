#ifndef CLOEXTENSIONS_PATTERNBUILDER_H
#define CLOEXTENSIONS_PATTERNBUILDER_H

#include "BaseExtension.h"

class PatternBuilder: public BaseExtension {
protected:
    ~PatternBuilder() override = default;

public:
    void configure(QWidget *widget) override;
    void configureStatusBar(QWidget *parent) override;
};


#endif //CLOEXTENSIONS_PATTERNBUILDER_H