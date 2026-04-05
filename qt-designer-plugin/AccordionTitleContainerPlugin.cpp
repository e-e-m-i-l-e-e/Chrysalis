#include "AccordionTitleContainerPlugin.h"

#include "AccordionTitleContainer.h"

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

QString AccordionTitleContainerPlugin::domXml() const {
    return R"(
<widget class="UI::AccordionTitleContainer" name="accordionTitleContainer">
    <widget class="QWidget" name="customWidget"/>
</widget>
)";
}
