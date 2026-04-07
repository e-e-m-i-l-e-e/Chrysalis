#include "Container.h"

using namespace UI;

Container::Container(QWidget *parent): QWidget(parent) {}

void Container::insertWidget(const int index, QWidget* widget) {
    getLayout()->insertWidget(index, widget);
}

QWidget* Container::getWidget(const int index) {
    return getLayout()->itemAt(index)->widget();
}
