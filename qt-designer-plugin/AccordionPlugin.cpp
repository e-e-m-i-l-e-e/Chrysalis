#include "AccordionPlugin.h"

#include <QExtensionManager>
#include <QDesignerFormEditorInterface>

#include "ExtensionFactory.h"
#include "AccordionContainerExtension.h"

QString AccordionPlugin::name() const {
    return QString("UI::Accordion");
}

QString AccordionPlugin::group() const {
    return QString("Custom Plugins");
}

QString AccordionPlugin::toolTip() const {
    return {};
}

QString AccordionPlugin::whatsThis() const {
    return {};
}

QString AccordionPlugin::includeFile() const {
    return "Accordion.h";
}

QIcon AccordionPlugin::icon() const {
    return QIcon();
}

bool AccordionPlugin::isContainer() const {
    return true;
}

QWidget * AccordionPlugin::createWidget(QWidget *parent) {
    return new UI::Accordion(parent);
}

bool AccordionPlugin::isInitialized() const {
    return QDesignerCustomWidgetInterface::isInitialized();
}

void AccordionPlugin::initialize(QDesignerFormEditorInterface *core) {
    const auto manager = core->extensionManager();
    manager->registerExtensions(new ExtensionFactory(manager), Q_TYPEID(QDesignerContainerExtension));
    QDesignerCustomWidgetInterface::initialize(core);
}

QString AccordionPlugin::domXml() const {
    return R"(
<ui language="c++">
  <widget class="UI::Accordion" name="accordion">
    <property name="geometry">
      <rect><x>0</x><y>0</y><width>300</width><height>200</height></rect>
    </property>
    <widget class="QWidget" name="titleWidget"/>
    <widget class="QWidget" name="contentWidget"/>
  </widget>
</ui>)";
}

QString AccordionPlugin::codeTemplate() const {
    return QDesignerCustomWidgetInterface::codeTemplate();
}
