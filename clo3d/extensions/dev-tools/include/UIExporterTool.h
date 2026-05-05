#ifndef FASHIONDESIGNAPPS_UIEXPORTERTOOL_H
#define FASHIONDESIGNAPPS_UIEXPORTERTOOL_H

#include <forward_list>

#include "BaseDevTool.h"
#include "BaseUIExporter.h"
#include "GeneralUIExporterOptions.h"
#include "UIExporterToolSettings.h"

class UIExporterTool: public BaseDevTool {
public:
    explicit UIExporterTool(UIExporterToolSettings* uiExporterToolSettings, GeneralUIExporterOptions* options);
    ~UIExporterTool() override;

    void configureSettings(ExtensionsSettings *extensionsSettings) override;
    void configureSettingsUI(UI::ExtensionsSettingsDialog *extensionsSettingsDialog) override;

    void addExporter(BaseUIExporter* exporter);
    // void readSettings() override;
    // void setSettings(const BaseExtensionsSettingsEditor* settingsEditor) override;
private:
    std::forward_list<BaseUIExporter*> exporters_;
    GeneralUIExporterOptions* options_;
    UIExporterToolSettings* uiExporterToolSettings_;
};


#endif //FASHIONDESIGNAPPS_UIEXPORTERTOOL_H