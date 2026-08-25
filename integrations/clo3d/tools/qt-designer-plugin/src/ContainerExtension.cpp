#include "ContainerExtension.h"


using namespace CLO3D::UI;

ContainerExtension::ContainerExtension(BaseContainer *container, QObject *parent)
    : QObject(parent), container_(container) {}

int ContainerExtension::count() const {
    return container_->count();
}

QWidget* ContainerExtension::widget(const int index) const {
    return container_->getWidget(index);
}

int ContainerExtension::currentIndex() const {
    return 0;
}

void ContainerExtension::setCurrentIndex(int index) {}

void ContainerExtension::addWidget(QWidget *widget) {
    container_->insertWidget(index_++, widget);
}

void ContainerExtension::insertWidget(int index, QWidget *widget) {}

void ContainerExtension::remove(int index) {}

bool ContainerExtension::canAddWidget() const {
    return false;
}

bool ContainerExtension::canRemove(int index) const {
    return false;
}
