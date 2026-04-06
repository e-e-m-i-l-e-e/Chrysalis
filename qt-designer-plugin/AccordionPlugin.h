#ifndef CLOEXTENSIONS_ACCORDIONPLUGIN_H
#define CLOEXTENSIONS_ACCORDIONPLUGIN_H

#include "ContainerPlugin.h"

class AccordionPlugin : public ContainerPlugin
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    QWidget* createWidget(QWidget *parent) override;
protected:
    [[nodiscard]] QString domXmlContent() const override;
};

#endif //CLOEXTENSIONS_ACCORDIONPLUGIN_H