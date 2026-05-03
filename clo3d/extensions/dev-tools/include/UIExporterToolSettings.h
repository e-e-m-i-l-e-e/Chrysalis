#ifndef FASHIONDESIGNAPPS_UIEXPORTERTOOL_H
#define FASHIONDESIGNAPPS_UIEXPORTERTOOL_H

#include <memory>
#include <forward_list>

#include "BaseExtensionsSettingsPage.h"

class BaseUIExporterOptions;

class UIExporterToolSettings: public BaseExtensionsSettingsPage {
public:
    void addOptions(const std::shared_ptr<BaseUIExporterOptions> &options);
    std::forward_list<std::shared_ptr<BaseUIExporterOptions>>::const_iterator begin() const;
    std::forward_list<std::shared_ptr<BaseUIExporterOptions>>::const_iterator end() const;
private:
    std::forward_list<std::shared_ptr<BaseUIExporterOptions>> options_;
};

#endif //FASHIONDESIGNAPPS_UIEXPORTERTOOL_H