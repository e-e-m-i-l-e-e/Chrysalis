#include "ContainerExtension.h"

ContainerExtension::ContainerExtension(QObject *parent): QObject(parent) {}

int ContainerExtension::currentIndex() const {
    return currentIndex_;
}

void ContainerExtension::setCurrentIndex(int index) {
    currentIndex_ = index;
}

void ContainerExtension::remove(int index) {}

bool ContainerExtension::canAddWidget() const {
    return false;
}

bool ContainerExtension::canRemove(int index) const {
    return false;
}
