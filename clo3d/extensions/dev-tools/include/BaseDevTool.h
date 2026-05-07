#ifndef FASHIONDESIGNAPPS_BASEDEVTOOL_H
#define FASHIONDESIGNAPPS_BASEDEVTOOL_H

#include "ExtensionsSettingsDialog.h"

class BaseDevTool {
    friend class DevToolsExtension;
protected:
    virtual ~BaseDevTool() = default;
public:
    virtual void configureSettings(ExtensionsSettings* extensionsSettings) = 0;
    virtual void configureSettingsUI(UI::ExtensionsSettingsDialog* extensionsSettingsDialog) = 0;
};

#endif //FASHIONDESIGNAPPS_BASEDEVTOOL_H