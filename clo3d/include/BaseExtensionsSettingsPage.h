#ifndef FASHIONDESIGNAPPS_BASEEXTENSIONSSETTINGSPAGE_H
#define FASHIONDESIGNAPPS_BASEEXTENSIONSSETTINGSPAGE_H

#include "BaseExtensionsSettingsEditor.h"

class BaseExtensionsSettingsPage: public BaseExtensionsSettingsEditor {
public:
    virtual void save() = 0;
    virtual void reset() = 0;
};

#endif //FASHIONDESIGNAPPS_BASEEXTENSIONSSETTINGSPAGE_H