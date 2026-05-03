#ifndef FASHIONDESIGNAPPS_EXTENSIONSSETTINGS_H
#define FASHIONDESIGNAPPS_EXTENSIONSSETTINGS_H

#include "BaseExtensionsSettingsEditor.h"

/// @uml{note[top] Exists during all app's lifetime.}
class ExtensionsSettings: public BaseExtensionsSettingsEditor {
public:
    ExtensionsSettings(const QString &organization, const QString &application);
};

#endif //FASHIONDESIGNAPPS_EXTENSIONSSETTINGS_H