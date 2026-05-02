#ifndef FASHIONDESIGNAPPS_BASEEXTENSIONSSETTINGSEDITOR_H
#define FASHIONDESIGNAPPS_BASEEXTENSIONSSETTINGSEDITOR_H

#include <QSettings>

class BaseExtensionsSettingsEditor {
public:
    virtual ~BaseExtensionsSettingsEditor();

    void setSettings(QSettings* settings);
    void setSettings(std::shared_ptr<BaseExtensionsSettingsEditor> settingsEditor);
    void editSettings(const QString& groupName, const std::function<void(QSettings*)>& editor) const;
private:
    QSettings* settings_ = nullptr;
};

#endif //FASHIONDESIGNAPPS_BASEEXTENSIONSSETTINGSEDITOR_H