#ifndef FASHIONDESIGNAPPS_EXTENSIONSSETTINGS_H
#define FASHIONDESIGNAPPS_EXTENSIONSSETTINGS_H

#include "BaseExtensionSettings.h"

class ExtensionsSettings {
public:
    ExtensionsSettings(const QString &organization, const QString &application);
    ~ExtensionsSettings();

    void read() const;
    void addSettings(BaseExtensionSettings* settings);
private:
    QSettings* settings_;
    std::forward_list<BaseExtensionSettings*> extensionsSettings_;
};

#endif //FASHIONDESIGNAPPS_EXTENSIONSSETTINGS_H