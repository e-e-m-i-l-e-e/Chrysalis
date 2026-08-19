#ifndef CHRYSALIS_BASEEXTENSIONSETTINGSWIDGET_H
#define CHRYSALIS_BASEEXTENSIONSETTINGSWIDGET_H

#include "CLO3DExtensionExport.h"

#include "NamedWidget.h"
#include "BaseExtensionSettings.h"

namespace CLO3D::UI {
    class CLO3D_EXTENSION BaseExtensionSettingsWidget: public NamedWidget {
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