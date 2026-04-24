#ifndef CLOEXTENSIONS_LISTNAVIGATIONPLUGIN_H
#define CLOEXTENSIONS_LISTNAVIGATIONPLUGIN_H

#include "ContainerPlugin.h"

class ListNavigationWidgetPlugin: public ContainerPlugin {

    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    QWidget* createWidget(QWidget *parent) override;
protected:
    [[nodiscard]] QStringList domXmlContent() const override;
};


#endif //CLOEXTENSIONS_LISTNAVIGATIONPLUGIN_H