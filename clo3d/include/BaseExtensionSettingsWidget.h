#ifndef FASHIONDESIGNAPPS_BASEEXTENSIONSETTINGSWIDGET_H
#define FASHIONDESIGNAPPS_BASEEXTENSIONSETTINGSWIDGET_H

#include "NamedWidget.h"
#include "BaseExtensionSettings.h"

namespace UI {
    class BaseExtensionSettingsWidget: public NamedWidget {
        Q_OBJECT
    public:
        explicit BaseExtensionSettingsWidget(BaseExtensionSettings& page, QWidget *parent)
            : NamedWidget(parent), page_(page) {}
        ~BaseExtensionSettingsWidget() override {
            // delete page_;
        }
        [[nodiscard]] BaseExtensionSettings& getBaseExtensionSettings() const {
            return page_;
        }
    public slots:
        virtual void save() {
            page_.writeSettings();
        };
        virtual void reset() = 0;
        virtual void read() {
            page_.readSettings();
        };
    private:
        BaseExtensionSettings& page_;
    };
}

#endif //FASHIONDESIGNAPPS_BASEEXTENSIONSETTINGSWIDGET_H