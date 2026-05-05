#ifndef FASHIONDESIGNAPPS_BASEEXTENSIONSSETTINGSEDITOR_H
#define FASHIONDESIGNAPPS_BASEEXTENSIONSSETTINGSEDITOR_H

#include "Settings.h"

class BaseExtensionsSettingsEditor {
public:
    BaseExtensionsSettingsEditor() = default;
    BaseExtensionsSettingsEditor(const QString &organization, const QString &application);
    virtual ~BaseExtensionsSettingsEditor() = default;

    virtual void setSettings(const BaseExtensionsSettingsEditor* settingsEditor);
    [[nodiscard]] Settings editSettings(const QString& groupName) const;
private:
    std::shared_ptr<QSettings> settings_;
};

#endif //FASHIONDESIGNAPPS_BASEEXTENSIONSSETTINGSEDITOR_H