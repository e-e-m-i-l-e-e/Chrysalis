#include "NamedWidgetPlugin.h"

#include "NamedWidget.h"

using namespace CLO3D::UI;

NamedWidgetPlugin::NamedWidgetPlugin(): WidgetPlugin() {}

QWidget* NamedWidgetPlugin::createWidget(QWidget* parent) {
    return new NamedWidget(parent);
}
