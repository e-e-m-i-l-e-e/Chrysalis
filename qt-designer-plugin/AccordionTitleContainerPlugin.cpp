#include "AccordionTitleContainerPlugin.h"

#include "AccordionTitleContainer.h"

QWidget* AccordionTitleContainerPlugin::createWidget(QWidget *parent) {
    return new UI::AccordionTitleContainer(parent);
}

QStringList AccordionTitleContainerPlugin::domXmlContent() const {
    return {containerXml("QWidget", "customWidget", "QHBoxLayout")};
}