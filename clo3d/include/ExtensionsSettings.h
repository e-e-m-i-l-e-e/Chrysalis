#ifndef FASHIONDESIGNAPPS_EXTENSIONSSETTINGS_H
#define FASHIONDESIGNAPPS_EXTENSIONSSETTINGS_H

#include "BaseExtensionsSettingsPage.h"
#include "BaseExtensionsSettingsEditor.h"

class ExtensionsSettings: public BaseExtensionsSettingsEditor {
public:
    ExtensionsSettings(const QString &organization, const QString &application);
    ~ExtensionsSettings() override;

    void addSettings(BaseExtensionsSettingsPage* settings);
    void readSettings() const;
private:
    std::forward_list<BaseExtensionsSettingsPage*> settings_;
};

#endif //FASHIONDESIGNAPPS_EXTENSIONSSETTINGS_H