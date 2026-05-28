#ifndef CHRYSALIS_TABLEINPUTACCORDIONPLUGIN_H
#define CHRYSALIS_TABLEINPUTACCORDIONPLUGIN_H

#include "ContainerPlugin.h"

class TableInputAccordionPlugin: public ContainerPlugin {

    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    QWidget* createWidget(QWidget *parent) override;
    protected:
    [[nodiscard]] QStringList domXmlContent() const override;
};


#endif //CHRYSALIS_TABLEINPUTACCORDIONPLUGIN_H