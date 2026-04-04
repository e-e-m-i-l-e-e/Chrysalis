#include "AccordionContainerExtension.h"

AccordionContainerExtension::AccordionContainerExtension(UI::Accordion *widget, QObject *parent) {
    this->accordion_ = widget;
}

AccordionContainerExtension::~AccordionContainerExtension() {
}

int AccordionContainerExtension::count() const {
    return 1;
}

QWidget * AccordionContainerExtension::widget(int index) const {
    return nullptr;
}

int AccordionContainerExtension::currentIndex() const {
    return 1;
}

void AccordionContainerExtension::setCurrentIndex(int index) {
}

void AccordionContainerExtension::addWidget(QWidget *widget) {
}

void AccordionContainerExtension::insertWidget(int index, QWidget *widget) {
}

void AccordionContainerExtension::remove(int index) {
}

bool AccordionContainerExtension::canAddWidget() const {
    return QDesignerContainerExtension::canAddWidget();
}

bool AccordionContainerExtension::canRemove(int index) const {
    return QDesignerContainerExtension::canRemove(index);
}
