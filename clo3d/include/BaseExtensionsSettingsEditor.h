#ifndef FASHIONDESIGNAPPS_BASEEXTENSIONSSETTINGSEDITOR_H
#define FASHIONDESIGNAPPS_BASEEXTENSIONSSETTINGSEDITOR_H

#include "Settings.h"

class BaseExtensionsSettingsEditor {
public:
    virtual ~BaseExtensionsSettingsEditor() = default;

    virtual void setSettings(QSettings* settings);
    [[nodiscard]] Settings editSettings(const QString& groupName) const;
private:
    QSettings* settings_ = nullptr;
};

#endif //FASHIONDESIGNAPPS_BASEEXTENSIONSSETTINGSEDITOR_H