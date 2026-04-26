#ifndef FASHIONDESIGNAPPS_BASEEXTENSIONSSETTINGSPAGEWIDGET_H
#define FASHIONDESIGNAPPS_BASEEXTENSIONSSETTINGSPAGEWIDGET_H

#include "NamedWidget.h"

namespace UI {
    class BaseExtensionsSettingsPageWidget: public NamedWidget {
        Q_OBJECT
    public:
        explicit BaseExtensionsSettingsPageWidget(QWidget *parent): NamedWidget(parent) {}
    public slots:
        virtual void save() = 0;
        virtual void reset() = 0;
        virtual void read() = 0;
    };
}

#endif //FASHIONDESIGNAPPS_BASEEXTENSIONSSETTINGSPAGEWIDGET_H