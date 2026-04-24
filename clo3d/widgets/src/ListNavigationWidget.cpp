#include "ListNavigationWidget.h"

#include <iostream>

#include "NamedWidget.h"
#include "ui_ListNavigationWidget.h"

using namespace UI;

ListNavigationWidget::ListNavigationWidget(QWidget *parent): QWidget(parent), ui(new Ui::ListNavigationWidget) {
    ui->setupUi(this);
    // ui->stackedWidget->setStyleSheet("background: red;");
    connect(ui->listWidget, &QListWidget::currentRowChanged, ui->stackedWidget, &QStackedWidget::setCurrentIndex);
}

ListNavigationWidget::~ListNavigationWidget() {
    delete ui;
}

void ListNavigationWidget::addPage(QWidget* page) const {
    ui->listWidget->addItem(page->objectName());
    ui->stackedWidget->addWidget(page);
    ui->stackedWidget->repaint();

    ui->listWidget->setCurrentRow(0);
}
