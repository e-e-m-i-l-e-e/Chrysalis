#ifndef CLOEXTENSIONS_TABLECONTENTPLUGIN_H
#define CLOEXTENSIONS_TABLECONTENTPLUGIN_H

#include "ContainerPlugin.h"

class TableContentContainerPlugin: public ContainerPlugin
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    QWidget* createWidget(QWidget *parent) override;
protected:
    [[nodiscard]] QStringList domXmlContent() const override;
};


#endif //CLOEXTENSIONS_TABLECONTENTPLUGIN_H