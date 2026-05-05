#ifndef FASHIONDESIGNAPPS_UIEXPORTERTOOL_H
#define FASHIONDESIGNAPPS_UIEXPORTERTOOL_H

#include <forward_list>

#include "BaseUIExporter.h"
#include "GeneralUIExporterOptions.h"
#include "BaseExtensionsSettingsPage.h"

class UIExporterTool: public BaseExtensionsSettingsPage {
public:
    explicit UIExporterTool(GeneralUIExporterOptions* options);
    ~UIExporterTool() override;

    void addExporter(BaseUIExporter* exporter);
    void readSettings() override;
    void setSettings(const BaseExtensionsSettingsEditor* settingsEditor) override;
private:
    std::forward_list<BaseUIExporter*> exporters_;
    GeneralUIExporterOptions* options_;
};


#endif //FASHIONDESIGNAPPS_UIEXPORTERTOOL_H