#ifndef FASHIONDESIGNAPPS_BASEEXTENSIONSETTINGS_H
#define FASHIONDESIGNAPPS_BASEEXTENSIONSETTINGS_H

#include <QSettings>

class BaseExtensionSettings {
public:
    virtual ~BaseExtensionSettings() = default;

    void setSettings(QSettings* settings);
    virtual void readSettings() = 0;
    virtual void writeSettings() = 0;
protected:
    QSettings* settings_ = nullptr;
};

#endif //FASHIONDESIGNAPPS_BASEEXTENSIONSETTINGS_H