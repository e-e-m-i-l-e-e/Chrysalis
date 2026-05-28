#ifndef CHRYSALIS_UIEXPORTERTOOL_H
#define CHRYSALIS_UIEXPORTERTOOL_H

#include <forward_list>

#include "BaseDevTool.h"
#include "BaseUIExporter.h"
#include "UIExporterToolSettings.h"
#include "GeneralUIExporterOptions.h"
#include "BaseNativeShortcutHandler.h"

class UIExporterTool: public BaseDevTool, public BaseNativeShortcutHandler {
public:
    explicit UIExporterTool(UIExporterToolSettings* uiExporterToolSettings, GeneralUIExporterOptions* options);
    ~UIExporterTool() override;

    static UIExporterTool* create();

    void configureSettings(ExtensionsSettings *extensionsSettings) override;
    void configureSettingsUI(UI::ExtensionsSettingsDialog *extensionsSettingsDialog) override;

    void handle() override;
    void addExporter(BaseUIExporter* exporter);
private:
    std::forward_list<BaseUIExporter*> exporters_;
    GeneralUIExporterOptions* options_;
    UIExporterToolSettings* uiExporterToolSettings_;
};


#endif //CHRYSALIS_UIEXPORTERTOOL_H