#include "ListNavigationWidgetPlugin.h"

#include "ListNavigationWidget.h"

using namespace CLO3D::UI;

QWidget* ListNavigationWidgetPlugin::createWidget(QWidget *parent) {
    return new ListNavigationWidget(parent);
}