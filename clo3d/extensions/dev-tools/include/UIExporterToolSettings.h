#ifndef FASHIONDESIGNAPPS_UIEXPORTERTOOLSETTINGS_H
#define FASHIONDESIGNAPPS_UIEXPORTERTOOLSETTINGS_H

#include <list>

#include "BaseUIExporterOptions.h"
#include "BaseExtensionSettings.h"

class UIExporterToolSettings: public BaseExtensionSettings {
public:
    void read() override;
    void write() override;

    void addOptions(BaseUIExporterOptions* options);

    [[nodiscard]] std::list<BaseUIExporterOptions*>::const_iterator begin() const;
    [[nodiscard]] std::list<BaseUIExporterOptions*>::const_iterator end() const;
private:
    std::list<BaseUIExporterOptions*> options_;
};

#endif //FASHIONDESIGNAPPS_UIEXPORTERTOOLSETTINGS_H