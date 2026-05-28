#include "SettingsBlockContainerWidgetPlugin.h"

#include "SettingsBlockContainerWidget.h"

QWidget* SettingsBlockContainerWidgetPlugin::createWidget(QWidget *parent) {
    return new UI::SettingsBlockContainerWidget(parent);
}

QStringList SettingsBlockContainerWidgetPlugin::domXmlContent() const {
    return {
        containerXml("customTools", "QHBoxLayout"),
        containerXml("settingsBlockContent", "QVBoxLayout")
    };
}
