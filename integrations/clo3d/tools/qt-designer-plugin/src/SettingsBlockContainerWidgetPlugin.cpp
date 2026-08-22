#include "SettingsBlockContainerWidgetPlugin.h"

#include "SettingsBlockContainerWidget.h"

using namespace CLO3D::UI;

QWidget* SettingsBlockContainerWidgetPlugin::createWidget(QWidget *parent) {
    return new SettingsBlockContainerWidget(parent);
}

QStringList SettingsBlockContainerWidgetPlugin::domXmlContent() const {
    return {
        containerXml("customTools", "QHBoxLayout"),
        containerXml("settingsBlockContent", "QVBoxLayout")
    };
}
