#include "AccordionTitleContainerExtension.h"

AccordionTitleContainerExtension::AccordionTitleContainerExtension(UI::AccordionTitleContainer* container, QObject* parent)
    : QObject(parent), container_(container) {}

int AccordionTitleContainerExtension::count() const {
    return 1;
}

QWidget * AccordionTitleContainerExtension::widget(int index) const {
    return container_->getCustomWidget();
}

int AccordionTitleContainerExtension::currentIndex() const {
    return 0;
}

void AccordionTitleContainerExtension::setCurrentIndex(int index) {}

void AccordionTitleContainerExtension::addWidget(QWidget *widget) {
    insertWidget(0, widget);
}

void AccordionTitleContainerExtension::insertWidget(int index, QWidget *widget) {
    if (index == 0) container_->setCustomWidget(widget);
}

void AccordionTitleContainerExtension::remove(int index) {}

bool AccordionTitleContainerExtension::canAddWidget() const {
    return false;
}

bool AccordionTitleContainerExtension::canRemove(int index) const {
    return false;
}
