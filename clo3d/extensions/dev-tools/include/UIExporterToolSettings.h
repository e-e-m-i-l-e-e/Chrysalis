#ifndef FASHIONDESIGNAPPS_UIEXPORTERTOOL_H
#define FASHIONDESIGNAPPS_UIEXPORTERTOOL_H

#include <forward_list>

#include "BaseExtensionsSettingsPage.h"

class BaseUIExporter;

class UIExporterToolSettings: public BaseExtensionsSettingsPage {
public:
    void save() override;
    void reset() override;
private:
    std::forward_list<BaseUIExporter*> exporters;
};

#endif //FASHIONDESIGNAPPS_UIEXPORTERTOOL_H