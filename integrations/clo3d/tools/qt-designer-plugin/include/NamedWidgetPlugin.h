#ifndef CHRYSALIS_NAMEDWIDGETPLUGIN_H
#define CHRYSALIS_NAMEDWIDGETPLUGIN_H
#include "WidgetPlugin.h"

class NamedWidgetPlugin: public WidgetPlugin {
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    NamedWidgetPlugin();

    QWidget* createWidget(QWidget *parent) override;
};


#endif //CHRYSALIS_NAMEDWIDGETPLUGIN_H