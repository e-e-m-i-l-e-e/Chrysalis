#ifndef FASHIONDESIGNAPPS_LOGGINGTOOL_H
#define FASHIONDESIGNAPPS_LOGGINGTOOL_H

#include "BaseDevTool.h"
#include "LoggingToolSettings.h"

class LoggingTool: public BaseDevTool {
public:
    explicit LoggingTool(LoggingToolSettings* settings);
    virtual ~LoggingTool();

    void configureSettings(ExtensionsSettings *extensionsSettings) override;
    void configureSettingsUI(UI::ExtensionsSettingsDialog *extensionsSettingsDialog) override;
private:
    LoggingToolSettings* settings_;
};

#endif //FASHIONDESIGNAPPS_LOGGINGTOOL_H