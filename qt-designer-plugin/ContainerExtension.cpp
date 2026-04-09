#include "ContainerExtension.h"

ContainerExtension::ContainerExtension(UI::BaseContainer *container, QObject *parent, const int count)
    : QObject(parent),
      container_(container),
      indexes_(QVector<int>(count)),
      it_([this] {
          std::iota(indexes_.begin(), indexes_.end(), 0);
          return QVectorIterator(indexes_);
      }()){}

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
