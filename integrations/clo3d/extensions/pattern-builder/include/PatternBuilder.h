#ifndef CHRYSALIS_PATTERNBUILDER_H
#define CHRYSALIS_PATTERNBUILDER_H

#include "BaseExtension.h"

class PatternBuilder: public BaseExtension {
protected:
    ~PatternBuilder() override = default;

public:
    void configure(QWidget *widget) override;
    void configureStatusBar(QWidget *parent) override;
};


#endif //CHRYSALIS_PATTERNBUILDER_H