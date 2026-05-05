#ifndef FASHIONDESIGNAPPS_BASEDEVTOOL_H
#define FASHIONDESIGNAPPS_BASEDEVTOOL_H

#include "ExtensionsSettings.h"
#include "ExtensionsSettingsDialog.h"

class BaseDevTool {
public:
    virtual ~BaseDevTool() = default;

    virtual void configureSettings(ExtensionsSettings* extensionsSettings) = 0;
    virtual void configureSettingsUI(UI::ExtensionsSettingsDialog* extensionsSettingsDialog) = 0;
};

#endif //FASHIONDESIGNAPPS_BASEDEVTOOL_H