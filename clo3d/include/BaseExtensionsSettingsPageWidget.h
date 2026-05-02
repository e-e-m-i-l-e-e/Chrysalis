#ifndef FASHIONDESIGNAPPS_BASEEXTENSIONSSETTINGSPAGEWIDGET_H
#define FASHIONDESIGNAPPS_BASEEXTENSIONSSETTINGSPAGEWIDGET_H

#include "NamedWidget.h"
#include "BaseExtensionsSettingsPage.h"

namespace UI {
    class BaseExtensionsSettingsPageWidget: public NamedWidget {
        Q_OBJECT
    public:
        explicit BaseExtensionsSettingsPageWidget(BaseExtensionsSettingsPage& page, QWidget *parent)
            : NamedWidget(parent), page_(page) {}
        ~BaseExtensionsSettingsPageWidget() override {
            // delete page_;
        }
        [[nodiscard]] BaseExtensionsSettingsPage& getBaseExtensionsSettingsPage() const {
            return page_;
        }
    public slots:
        virtual void save() = 0;
        virtual void reset() = 0;
        virtual void read() = 0;
    private:
        BaseExtensionsSettingsPage& page_;
    };
}

#endif //FASHIONDESIGNAPPS_BASEEXTENSIONSSETTINGSPAGEWIDGET_H