#include "BaseUIExporterSettingsBlockContainerWidgetPlugin.h"

#include "BaseUIExporterSettingsBlockContainerWidget.h"

QWidget* BaseUIExporterSettingsBlockContainerWidgetPlugin::createWidget(QWidget *parent) {
    return new UI::BaseUIExporterSettingsBlockContainerWidget(parent);
}

QStringList BaseUIExporterSettingsBlockContainerWidgetPlugin::domXmlContent() const {
    return {
        containerXml("customTools", "QHBoxLayout"),
        containerXml("settingsLeftBlockContent", "QFormLayout"),
        containerXml("settingsRightBlockContent", "QFormLayout")
    };
}
