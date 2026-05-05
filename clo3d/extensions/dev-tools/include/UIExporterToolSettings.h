#ifndef FASHIONDESIGNAPPS_UIEXPORTERTOOLSETTINGS_H
#define FASHIONDESIGNAPPS_UIEXPORTERTOOLSETTINGS_H

#include <memory>
#include <forward_list>

#include "BaseUIExporterOptions.h"
#include "BaseExtensionsSettingsPage.h"

class UIExporterToolSettings: public BaseExtensionsSettingsPage {
public:
    void readSettings() override {};
    void addOptions(const std::shared_ptr<BaseUIExporterOptions> &options);

    std::forward_list<std::shared_ptr<BaseUIExporterOptions>>::const_iterator begin() const;
    std::forward_list<std::shared_ptr<BaseUIExporterOptions>>::const_iterator end() const;
private:
    std::forward_list<std::shared_ptr<BaseUIExporterOptions>> options_;
};

#endif //FASHIONDESIGNAPPS_UIEXPORTERTOOLSETTINGS_H