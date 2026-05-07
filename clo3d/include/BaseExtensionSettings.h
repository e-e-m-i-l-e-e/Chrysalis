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
    virtual void read() = 0;
    virtual void write() = 0;
protected:
    QSettings* settings_ = nullptr;
};

#endif //FASHIONDESIGNAPPS_BASEEXTENSIONSETTINGS_H