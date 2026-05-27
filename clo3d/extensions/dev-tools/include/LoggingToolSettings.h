#ifndef FASHIONDESIGNAPPS_LOGGINGTOOLSETTINGS_H
#define FASHIONDESIGNAPPS_LOGGINGTOOLSETTINGS_H

#include "unordered_map"

#include "BaseExtensionSettings.h"

class LoggingToolSettings: public BaseExtensionSettings {
public:
    void read() override;
    void write() override;
};

#endif //FASHIONDESIGNAPPS_LOGGINGTOOLSETTINGS_H