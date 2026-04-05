#include "AccordionTitleContainerPlugin.h"

#include <QExtensionManager>
#include <QDesignerFormEditorInterface>

#include "AccordionTitleContainerExtension.h"
#include "ExtensionFactory.h"

QString AccordionTitleContainerPlugin::name() const {
    return "UI::AccordionTitleContainer";
}

QString AccordionTitleContainerPlugin::group() const {
    return "Containers";
}

QString AccordionTitleContainerPlugin::toolTip() const {
    return {};
}

QString AccordionTitleContainerPlugin::whatsThis() const {
    return {};
}

QString AccordionTitleContainerPlugin::includeFile() const {
    return "AccordionTitleContainer.h";
}

QIcon AccordionTitleContainerPlugin::icon() const {
    return {};
}

bool AccordionTitleContainerPlugin::isContainer() const {
    return true;
}

QWidget * AccordionTitleContainerPlugin::createWidget(QWidget *parent) {
    return new UI::AccordionTitleContainer(parent);
}

bool AccordionTitleContainerPlugin::isInitialized() const {
    return m_initialized;
}

void AccordionTitleContainerPlugin::initialize(QDesignerFormEditorInterface *core) {
    if (m_initialized) return;
    auto* manager = core->extensionManager();
    manager->registerExtensions(new ExtensionFactory(manager), Q_TYPEID(QDesignerContainerExtension));
    m_initialized = true;
}

QString AccordionTitleContainerPlugin::domXml() const {
    return R"(
<widget class="UI::AccordionTitleContainer" name="accordionTitleContainer">
    <widget class="QWidget" name="customWidget"/>
</widget>
)";
}
