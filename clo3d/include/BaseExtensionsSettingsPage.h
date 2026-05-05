#ifndef FASHIONDESIGNAPPS_BASEEXTENSIONSSETTINGSPAGE_H
#define FASHIONDESIGNAPPS_BASEEXTENSIONSSETTINGSPAGE_H

#include "BaseExtensionsSettingsEditor.h"

class BaseExtensionsSettingsPage: public BaseExtensionsSettingsEditor {
public:
    virtual void readSettings() = 0;
};

#endif //FASHIONDESIGNAPPS_BASEEXTENSIONSSETTINGSPAGE_H