#ifndef CHRYSALIS_PATTERNBUILDER_H
#define CHRYSALIS_PATTERNBUILDER_H

#include "BaseExtension.h"

namespace CLO3D {
    class ChrysalisExtension: public BaseExtension {
    public:
        ~ChrysalisExtension() override = default;

        void configure(QWidget *widget) override;
        void configureMenu(QMenu* extensionMenu) override;
        void configureStatusBar(QWidget *parent) override;
        void configureLocalServer(LocalServer* localServer) override;
    };
}

#endif //CHRYSALIS_PATTERNBUILDER_H