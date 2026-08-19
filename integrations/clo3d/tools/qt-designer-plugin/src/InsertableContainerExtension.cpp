#include "InsertableContainerExtension.h"

using namespace CLO3D::UI;

InsertableContainerExtension::InsertableContainerExtension(UI::BaseInsertableContainer *container, QObject *parent)
    : ContainerExtension(container, parent), container_(container) {}

int InsertableContainerExtension::count() const {
    return container_->count();
}

QWidget* InsertableContainerExtension::widget(int index) const {
    return container_->getWidget(index);
}

int InsertableContainerExtension::currentIndex() const {
    return currentIndex_;
}

void InsertableContainerExtension::setCurrentIndex(int index) {
    currentIndex_ = index;
}

void InsertableContainerExtension::insertWidget(int index, QWidget *widget) {
    container_->insertWidget(index, widget);
}

void InsertableContainerExtension::remove(int index) {
    container_->remove(index);
    setCurrentIndex(std::max(0, std::min(currentIndex_, this->count() - 1)));
}

bool InsertableContainerExtension::canAddWidget() const {
    return true;
}

bool InsertableContainerExtension::canRemove(int index) const {
    return container_->count() > 0;
}