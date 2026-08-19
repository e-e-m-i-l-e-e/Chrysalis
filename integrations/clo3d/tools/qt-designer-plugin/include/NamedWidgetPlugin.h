#ifndef CHRYSALIS_NAMEDWIDGETPLUGIN_H
#define CHRYSALIS_NAMEDWIDGETPLUGIN_H
#include "WidgetPlugin.h"

namespace CLO3D::UI {
    class NamedWidgetPlugin: public WidgetPlugin {
        Q_OBJECT
        Q_INTERFACES(QDesignerCustomWidgetInterface)
    public:
        NamedWidgetPlugin();

        QWidget* createWidget(QWidget *parent) override;
    };
}

#endif //CHRYSALIS_NAMEDWIDGETPLUGIN_H