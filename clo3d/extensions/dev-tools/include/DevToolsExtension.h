#ifndef FASHIONDESIGNAPPS_DEVTOOLSEXTENSION_H
#define FASHIONDESIGNAPPS_DEVTOOLSEXTENSION_H

#include "Extension.h"
#include "UIExporterTool.h"

class DevToolsExtension: public Extension {
public:
    void install() override;
    void configureSettings(ExtensionsSettings* extensionsSettings) override;
private:
    UIExporterTool* uiExporterTool = nullptr;
};

#endif //FASHIONDESIGNAPPS_DEVTOOLSEXTENSION_H