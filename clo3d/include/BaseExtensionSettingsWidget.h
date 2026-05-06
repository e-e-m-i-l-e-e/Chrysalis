#ifndef FASHIONDESIGNAPPS_BASEEXTENSIONSETTINGSWIDGET_H
#define FASHIONDESIGNAPPS_BASEEXTENSIONSETTINGSWIDGET_H

#include "NamedWidget.h"
#include "BaseExtensionSettings.h"

namespace UI {
    class BaseExtensionSettingsWidget: public NamedWidget {
        Q_OBJECT
    public:
        explicit BaseExtensionSettingsWidget(BaseExtensionSettings* extensionSettings, QWidget *parent);
        [[nodiscard]] BaseExtensionSettings* getBaseExtensionSettings() const;
    public slots:
        virtual void save();
        virtual void reset() = 0;
        virtual void read();
    private:
        BaseExtensionSettings* extensionSettings_;
    };
}

#endif //FASHIONDESIGNAPPS_BASEEXTENSIONSETTINGSWIDGET_H