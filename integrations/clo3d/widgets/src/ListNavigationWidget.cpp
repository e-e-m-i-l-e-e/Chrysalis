#include "ListNavigationWidget.h"

#include <iostream>

#include "NamedWidget.h"
#include "ui_ListNavigationWidget.h"

using namespace UI;

ListNavigationWidget::ListNavigationWidget(QWidget *parent): QWidget(parent), ui(new Ui::ListNavigationWidget) {
    ui->setupUi(this);
}

ListNavigationWidget::~ListNavigationWidget() {
    delete ui;
}

int ListNavigationWidget::count() const {
    return ui->stackedWidget->count();
}

void ListNavigationWidget::addPage(NamedWidget* page) const {
    ui->listWidget->addItem(page->getTitle());
    ui->listWidget->setFixedWidth(std::max(ui->listWidget->width(), ui->listWidget->sizeHintForColumn(ui->listWidget->count() - 1) + 4));
    ui->stackedWidget->addWidget(page);
    ui->listWidget->setCurrentRow(0);
}

NamedWidget * ListNavigationWidget::getPage(const int index) const {
    return qobject_cast<NamedWidget*>(ui->stackedWidget->widget(index));
}
