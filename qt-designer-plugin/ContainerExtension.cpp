#include "ContainerExtension.h"

#include <utility>

ContainerExtension::ContainerExtension(UI::Container* container, QObject* parent, const int count)
    : ContainerExtension(container, parent, QVector<int>(count)) {
    std::iota(indexes_.begin(), indexes_.end(), 0);
    it_ = QVectorIterator(indexes_);
}

ContainerExtension::ContainerExtension(UI::Container *container, QObject *parent, QVector<int> indexes)
    : QObject(parent),
      container_(container),
      indexes_(std::move(indexes)),
      it_(indexes_) {}

int ContainerExtension::count() const {
    return indexes_.count();
}

QWidget* ContainerExtension::widget(int index) const {
    return container_->getWidget(indexes_[index]);
}

int ContainerExtension::currentIndex() const {
    return 0;
}

void ContainerExtension::setCurrentIndex(int index) {}

void ContainerExtension::addWidget(QWidget *widget) {
    container_->insertWidget(it_.next(), widget);
}

void ContainerExtension::insertWidget(int index, QWidget *widget) {}

void ContainerExtension::remove(int index) {}

bool ContainerExtension::canAddWidget() const {
    return false;
}

bool ContainerExtension::canRemove(int index) const {
    return false;
}
