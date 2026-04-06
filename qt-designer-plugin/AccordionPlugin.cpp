#include "AccordionPlugin.h"

#include "Accordion.h"
#include "AccordionTitleContainerPlugin.h"
#include "DesignerPlugin.h"

QWidget * AccordionPlugin::createWidget(QWidget *parent) {
    return new UI::Accordion(parent);
}

QString AccordionPlugin::domXmlContent() const {
    return QString(R"(
    %1
    %2
)")
    .arg(DesignerPlugin::accordionTitleContainerPlugin->domXml())
    .arg(containerXml("QWidget", "contentWidget", "QVBoxLayout"));
}
