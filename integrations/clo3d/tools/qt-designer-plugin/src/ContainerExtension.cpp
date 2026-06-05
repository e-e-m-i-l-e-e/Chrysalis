#include "ContainerExtension.h"

#include <iostream>

ContainerExtension::ContainerExtension(UI::BaseContainer *container, QObject *parent)
    : QObject(parent), container_(container) {}

int ContainerExtension::count() const {
    return container_->count();
}

QWidget* ContainerExtension::widget(int index) const {
    std::cout << "Get widget: " << index << std::endl;
    return container_->getWidget(index);
}

int ContainerExtension::currentIndex() const {
    return 0;
}

void ContainerExtension::setCurrentIndex(int index) {}

void ContainerExtension::addWidget(QWidget *widget) {
    std::cout << "Add widget" << std::endl;
    container_->insertWidget(index_++, widget);
}

void ContainerExtension::insertWidget(int index, QWidget *widget)
{
    std::cout << "Insert widget" << std::endl;
}

void ContainerExtension::remove(int index) {}

bool ContainerExtension::canAddWidget() const {
    return false;
}

bool ContainerExtension::canRemove(int index) const {
    return false;
}
