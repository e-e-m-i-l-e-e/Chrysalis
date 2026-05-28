#ifndef CHRYSALIS_BASEEXTENSIONSETTINGSWIDGET_H
#define CHRYSALIS_BASEEXTENSIONSETTINGSWIDGET_H

#include "NamedWidget.h"
#include "BaseExtensionSettings.h"

namespace UI {
    class BaseExtensionSettingsWidget: public NamedWidget {
        Q_OBJECT
    public:
        explicit BaseExtensionSettingsWidget(BaseExtensionSettings* extensionSettings, QWidget *parent);
        [[nodiscard]] BaseExtensionSettings* getBaseExtensionSettings() const;
    public slots:
        virtual void read();
        virtual void write();
    private:
        BaseExtensionSettings* extensionSettings_;
    };
}

#endif //CHRYSALIS_BASEEXTENSIONSETTINGSWIDGET_H