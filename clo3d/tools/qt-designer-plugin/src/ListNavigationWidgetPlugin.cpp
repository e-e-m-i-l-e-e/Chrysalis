#include "ListNavigationWidgetPlugin.h"

#include "ListNavigationWidget.h"

QWidget* ListNavigationWidgetPlugin::createWidget(QWidget *parent) {
    return new UI::ListNavigationWidget(parent);
}

QStringList ListNavigationWidgetPlugin::domXmlContent() const {
    return {
        containerXml("QWidget", "page", "QVBoxLayout"),
    };
}
