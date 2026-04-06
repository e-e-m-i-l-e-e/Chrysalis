#include "AccordionContainerPlugin.h"

#include "AccordionContainer.h"
#include "AccordionTitleContainerPlugin.h"
#include "DesignerPlugin.h"

QWidget* AccordionContainerPlugin::createWidget(QWidget *parent) {
    return new UI::AccordionContainer(parent);
}

QStringList AccordionContainerPlugin::domXmlContent() const {
    return {
        DesignerPlugin::accordionTitleContainerPlugin->domXml(),
        containerXml("QWidget", "contentWidget", "QVBoxLayout")
    };
}
