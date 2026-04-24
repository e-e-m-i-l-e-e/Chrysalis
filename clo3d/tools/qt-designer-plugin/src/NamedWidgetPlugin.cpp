#include "NamedWidgetPlugin.h"

#include "NamedWidget.h"

NamedWidgetPlugin::NamedWidgetPlugin(): WidgetPlugin() {}

QWidget* NamedWidgetPlugin::createWidget(QWidget* parent) {
    return new UI::NamedWidget(parent);
}
