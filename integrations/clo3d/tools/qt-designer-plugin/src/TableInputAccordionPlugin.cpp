#include "TableInputAccordionPlugin.h"

#include "TableInputAccordion.h"

using namespace CLO3D::UI;

QWidget* TableInputAccordionPlugin::createWidget(QWidget *parent) {
    return new TableInputAccordion(parent);
}

QStringList TableInputAccordionPlugin::domXmlContent() const {
    return {
        containerXml("customTools", "QHBoxLayout"),
        containerXml("beforeTable", "QVBoxLayout"),
        containerXml("afterTable", "QVBoxLayout")
    };
}
