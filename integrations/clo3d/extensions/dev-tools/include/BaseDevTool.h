#ifndef CHRYSALIS_BASEDEVTOOL_H
#define CHRYSALIS_BASEDEVTOOL_H

#include "ExtensionsSettingsDialog.h"

class BaseDevTool {
    friend class DevToolsExtension;
protected:
    virtual ~BaseDevTool() = default;
public:
    virtual void startup();
    virtual void configureSettings(ExtensionsSettings* extensionsSettings) = 0;
    virtual void configureSettingsUI(UI::ExtensionsSettingsDialog* extensionsSettingsDialog) = 0;
};

#endif //CHRYSALIS_BASEDEVTOOL_H