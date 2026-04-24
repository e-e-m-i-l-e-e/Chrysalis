#include "ListNavigationWidgetPlugin.h"

#include "ListNavigationWidget.h"

QWidget* ListNavigationWidgetPlugin::createWidget(QWidget *parent) {
    return new UI::ListNavigationWidget(parent);
}