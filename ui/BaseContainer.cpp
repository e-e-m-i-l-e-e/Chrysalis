#include "BaseContainer.h"

using namespace UI;

BaseContainer::BaseContainer(QWidget *parent): QWidget(parent) {}

void BaseContainer::install(const QList<QWidget*>& widgets) {
    for (int i = 0; i < widgets.length(); i++) {
        insertWidget(i, widgets.at(i));
    }
}
