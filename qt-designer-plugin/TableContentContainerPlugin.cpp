#include "TableContentContainerPlugin.h"

#include "TableContentContainer.h"

QWidget * TableContentContainerPlugin::createWidget(QWidget *parent) {
    return new UI::TableContentContainer(parent);
}

QStringList TableContentContainerPlugin::domXmlContent() const {
    return {
        containerXml("QWidget", "before", "QVBoxLayout"),
        containerXml("QWidget", "after", "QVBoxLayout")
    };
}
