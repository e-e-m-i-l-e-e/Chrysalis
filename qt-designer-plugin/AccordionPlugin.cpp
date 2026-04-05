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
}

QString AccordionPlugin::domXml() const {
    return R"(
<widget class="UI::Accordion" name="accordion">
    <widget class="UI::AccordionTitleContainer" name="titleWidget"/>
    <widget class="QWidget" name="contentWidget"/>
 </widget>
)";
}
