#ifndef CHRYSALIS_EXTENSIONSSETTINGS_H
#define CHRYSALIS_EXTENSIONSSETTINGS_H

#include "BaseExtensionSettings.h"

class ExtensionsSettings {
public:
    ExtensionsSettings(const QString &organization, const QString &application);
    ~ExtensionsSettings();

    void read() const;
    void clear() const;
    void addSettings(BaseExtensionSettings* settings);
private:
    QSettings* settings_;
    std::forward_list<BaseExtensionSettings*> extensionsSettings_;
};

#endif //CHRYSALIS_EXTENSIONSSETTINGS_H