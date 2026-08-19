#ifndef CHRYSALIS_BASEEXTENSIONSETTINGS_H
#define CHRYSALIS_BASEEXTENSIONSETTINGS_H

#include <QSettings>

namespace CLO3D {
    class BaseExtensionSettings {
        friend class ExtensionsSettings;
    protected:
        virtual ~BaseExtensionSettings() = default;

        virtual void read() = 0;
        virtual void write() = 0;
    private:
        void setSettings(QSettings* settings);
    public:
        void readSettings();
        void writeSettings();
    protected:
        QSettings* settings_ = nullptr;
    };
}

#endif //CHRYSALIS_BASEEXTENSIONSETTINGS_H