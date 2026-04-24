#include "ListNavigationWidget.h"

#include <iostream>

#include "NamedWidget.h"
#include "ui_ListNavigationWidget.h"

using namespace UI;

ListNavigationWidget::ListNavigationWidget(QWidget *parent) : BaseInsertableContainer(parent), ui(new Ui::ListNavigationWidget) {
    ui->setupUi(this);
}

ListNavigationWidget::~ListNavigationWidget() {
    delete ui;
}

int ListNavigationWidget::count() const {
    return ui->stackedWidget->count();
}

void ListNavigationWidget::remove(const int index) {
    delete ui->listWidget->takeItem(index);
    ui->stackedWidget->removeWidget(ui->stackedWidget->widget(index));
}

void ListNavigationWidget::insertWidget(const int index, QWidget *widget) {
    std::cout << "Adding widget: " << widget->metaObject()->className() << std::endl;
    widget->setProperty("name", "Replace \"name\" property value");
    ui->listWidget->insertItem(index, widget->property("name").toString());
    ui->stackedWidget->insertWidget(index, widget);
}

QWidget* ListNavigationWidget::getWidget(const int index) {
    return ui->stackedWidget->widget(index);
}
