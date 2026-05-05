#ifndef FASHIONDESIGNAPPS_UIEXPORTERTOOLSETTINGS_H
#define FASHIONDESIGNAPPS_UIEXPORTERTOOLSETTINGS_H

#include <list>

#include "BaseUIExporterOptions.h"
#include "BaseExtensionsSettingsPage.h"

class UIExporterToolSettings: public BaseExtensionsSettingsPage {
public:
    void readSettings() override {};
    void addOptions(BaseUIExporterOptions* options);

    std::list<BaseUIExporterOptions*>::const_iterator begin() const;
    std::list<BaseUIExporterOptions*>::const_iterator end() const;
private:
    std::list<BaseUIExporterOptions*> options_;
};

#endif //FASHIONDESIGNAPPS_UIEXPORTERTOOLSETTINGS_H