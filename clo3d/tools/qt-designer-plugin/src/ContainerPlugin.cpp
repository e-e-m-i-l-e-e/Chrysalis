#include "ContainerPlugin.h"

#include <QExtensionManager>
#include <QDesignerContainerExtension>
#include <QDesignerFormEditorInterface>

#include "ExtensionFactory.h"

#include <iostream>

static const QString basicWidget = R"(
<widget class="%1" name="%2">
    %3
</widget>
)";

static const QString basicLayout = R"(
<layout class="%3" name="layout">
    <property name="leftMargin"><number>0</number></property>
    <property name="topMargin"><number>0</number></property>
    <property name="rightMargin"><number>0</number></property>
    <property name="bottomMargin"><number>0</number></property>
    <property name="spacing"><number>0</number></property>
</layout>
)";

QString ContainerPlugin::group() const {
    return "Containers";
}

bool ContainerPlugin::isContainer() const {
    return true;
}

QString ContainerPlugin::containerXml(const QString &objectName, const QString &layoutClassName) {
    return containerXml("QWidget", objectName, layoutClassName);
}

QString ContainerPlugin::containerXml(const QString &className, const QString &objectName, const QString &layoutClassName) {
    return basicWidget.arg(className).arg(objectName).arg(basicLayout.arg(layoutClassName));
}

QString ContainerPlugin::domXml() const {
    const auto className = name();
    auto objectName = className;
    objectName.remove(0, 4); // remove namespace
    objectName[0] = objectName[0].toLower(); // start objectName in lower case
    return basicWidget.arg(className).arg(objectName).arg(domXmlContent().join("\n"));
}

void ContainerPlugin::initialize(QDesignerFormEditorInterface *core) {
    WidgetPlugin::initialize(core);
    const auto manager = core->extensionManager();
    manager->registerExtensions(new ExtensionFactory(manager), Q_TYPEID(QDesignerContainerExtension));
}
