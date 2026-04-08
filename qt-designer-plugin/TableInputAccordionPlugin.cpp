#include "TableInputAccordionPlugin.h"

#include "TableInputAccordion.h"

QWidget* TableInputAccordionPlugin::createWidget(QWidget *parent) {
    return new UI::TableInputAccordion(parent);
}

QStringList TableInputAccordionPlugin::domXmlContent() const {
    return {
        containerXml("customTools", "QHBoxLayout"),
        containerXml("beforeTable", "QVBoxLayout"),
        containerXml("afterTable", "QVBoxLayout")
    };
}
