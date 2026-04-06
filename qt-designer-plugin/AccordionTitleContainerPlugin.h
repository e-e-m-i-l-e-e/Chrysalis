#ifndef CLOEXTENSIONS_ACCORDIONTITLECONTAINERPLUGIN_H
#define CLOEXTENSIONS_ACCORDIONTITLECONTAINERPLUGIN_H

#include "ContainerPlugin.h"
#include "WidgetPlugin.h"

class AccordionTitleContainerPlugin: public ContainerPlugin {

    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    QWidget* createWidget(QWidget *parent) override;
protected:
    [[nodiscard]] QStringList domXmlContent() const override;
};


#endif //CLOEXTENSIONS_ACCORDIONTITLECONTAINERPLUGIN_H