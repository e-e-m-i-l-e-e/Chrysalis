#ifndef CHRYSALIS_PATTERNBUILDER_H
#define CHRYSALIS_PATTERNBUILDER_H

#include "BaseExtension.h"

namespace Chrysalis {
    class ChrysalisExtension: public BaseExtension {
    protected:
        ~ChrysalisExtension() override = default;

    public:
        void configure(QWidget *widget) override;
        void configureMenu(QMenu* extensionMenu) override;
        void configureStatusBar(QWidget *parent) override;
    };
}

#endif //CHRYSALIS_PATTERNBUILDER_H