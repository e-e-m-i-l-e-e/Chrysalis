#ifndef FASHIONDESIGNAPPS_BASEEXTENSIONSSETTINGSEDITOR_H
#define FASHIONDESIGNAPPS_BASEEXTENSIONSSETTINGSEDITOR_H

#include "Settings.h"

class BaseExtensionsSettingsEditor {
public:
    virtual ~BaseExtensionsSettingsEditor() = 0;

    void setSettings(QSettings* settings);
    void setSettings(std::shared_ptr<BaseExtensionsSettingsEditor> settingsEditor);
    [[nodiscard]] Settings editSettings(const QString& groupName) const;
private:
    QSettings* settings_ = nullptr;
};

#endif //FASHIONDESIGNAPPS_BASEEXTENSIONSSETTINGSEDITOR_H