#include "AccordionTitleContainerPlugin.h"

#include "AccordionTitleContainer.h"

QWidget* AccordionTitleContainerPlugin::createWidget(QWidget *parent) {
    return new UI::AccordionTitleContainer(parent);
}

QString AccordionTitleContainerPlugin::domXmlContent() const {
    return containerXml("QWidget", "customWidget", "QHBoxLayout");
}
