#ifndef CLOEXTENSIONS_LISTNAVIGATIONPLUGIN_H
#define CLOEXTENSIONS_LISTNAVIGATIONPLUGIN_H

#include "WidgetPlugin.h"

class ListNavigationWidgetPlugin: public WidgetPlugin {

    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    QWidget* createWidget(QWidget *parent) override;
};


#endif //CLOEXTENSIONS_LISTNAVIGATIONPLUGIN_H