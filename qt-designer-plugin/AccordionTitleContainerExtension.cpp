#include "AccordionTitleContainerExtension.h"

AccordionTitleContainerExtension::AccordionTitleContainerExtension(UI::AccordionTitleContainer* container, QObject* parent)
    : ContainerExtension(parent), container_(container) {}

int AccordionTitleContainerExtension::count() const {
    return 1;
}

QWidget * AccordionTitleContainerExtension::widget(int index) const {
    return container_->getCustomWidget();
}

void AccordionTitleContainerExtension::addWidget(QWidget *widget) {
    insertWidget(0, widget);
}

void AccordionTitleContainerExtension::insertWidget(int index, QWidget *widget) {
    if (index == 0) container_->setCustomWidget(widget);
}
