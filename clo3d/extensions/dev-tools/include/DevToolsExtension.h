#ifndef FASHIONDESIGNAPPS_DEVTOOLSEXTENSION_H
#define FASHIONDESIGNAPPS_DEVTOOLSEXTENSION_H

#include "BaseExtension.h"
#include "BaseDevTool.h"
#include "UIExporterTool.h"

class DevToolsExtension: public BaseExtension {
public:
    ~DevToolsExtension() override;

    void addDevTool(BaseDevTool* tool);
    void configureSettings(ExtensionsSettings* extensionsSettings) override;
    void configureSettingsUI(UI::ExtensionsSettingsDialog *extensionsSettingsDialog) override;
private:
    std::forward_list<BaseDevTool*> devTools_;
};

#endif //FASHIONDESIGNAPPS_DEVTOOLSEXTENSION_H