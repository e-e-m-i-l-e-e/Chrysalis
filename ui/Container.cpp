#include "Container.h"

#include <QLayout>

using namespace UI;

Container::Container(QWidget *parent): QWidget(parent) {}

int Container::count() const {
    return customWidgets.count();
}

void Container::insertWidget(int index, QWidget* widget) {
    customWidgets.append(widget);
    getLayout()->addWidget(widget);
}

QWidget* Container::getWidget(const int index) const {
    return customWidgets[index];
}
