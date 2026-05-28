#ifndef FASHIONDESIGNAPPS_UIEXPORTERTOOL_H
#define FASHIONDESIGNAPPS_UIEXPORTERTOOL_H

#include <forward_list>

#include "BaseDevTool.h"
#include "BaseNativeShortcutHandler.h"
#include "BaseUIExporter.h"
#include "GeneralUIExporterOptions.h"
#include "UIExporterToolSettings.h"

/*
 *  TODO:
 *      - add ability to stop export
 *      - add overall progress tracker
 */

class UIExporterTool: public BaseDevTool, public BaseNativeShortcutHandler {
public:
    explicit UIExporterTool(UIExporterToolSettings* uiExporterToolSettings, GeneralUIExporterOptions* options);
    ~UIExporterTool() override;

    void configureSettings(ExtensionsSettings *extensionsSettings) override;
    void configureSettingsUI(UI::ExtensionsSettingsDialog *extensionsSettingsDialog) override;

    void handle() override;
    void addExporter(BaseUIExporter* exporter);
private:
    std::forward_list<BaseUIExporter*> exporters_;
    GeneralUIExporterOptions* options_;
    UIExporterToolSettings* uiExporterToolSettings_;
};


#endif //FASHIONDESIGNAPPS_UIEXPORTERTOOL_H