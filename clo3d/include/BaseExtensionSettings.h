#ifndef FASHIONDESIGNAPPS_BASEEXTENSIONSETTINGS_H
#define FASHIONDESIGNAPPS_BASEEXTENSIONSETTINGS_H

#include "BaseExtensionsSettingsEditor.h"

class BaseExtensionSettings: public BaseExtensionsSettingsEditor {
public:
    virtual void readSettings() = 0;
    virtual void writeSettings() = 0;
};

#endif //FASHIONDESIGNAPPS_BASEEXTENSIONSETTINGS_H