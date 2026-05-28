#ifndef CHRYSALIS_LISTNAVIGATIONPLUGIN_H
#define CHRYSALIS_LISTNAVIGATIONPLUGIN_H

#include "WidgetPlugin.h"

class ListNavigationWidgetPlugin: public WidgetPlugin {

    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    QWidget* createWidget(QWidget *parent) override;
};


#endif //CHRYSALIS_LISTNAVIGATIONPLUGIN_H