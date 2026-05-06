#ifndef FASHIONDESIGNAPPS_BASEEXTENSIONSETTINGS_H
#define FASHIONDESIGNAPPS_BASEEXTENSIONSETTINGS_H

#include <QSettings>

class BaseExtensionSettings {
    friend class ExtensionsSettings;
protected:
    virtual ~BaseExtensionSettings() = default;
private:
    void setSettings(QSettings* settings);
public:
    virtual void readSettings() = 0;
    virtual void writeSettings() = 0;
protected:
    QSettings* settings_ = nullptr;
};

#endif //FASHIONDESIGNAPPS_BASEEXTENSIONSETTINGS_H