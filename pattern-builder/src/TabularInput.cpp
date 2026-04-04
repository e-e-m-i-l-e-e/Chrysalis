//
// Created by emily on 03/04/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_TabularInput.h" resolved

#include "TabularInput.h"

#include <CLOAPIInterface.h>

#include "ui_TabularInput.h"


TabularInput::TabularInput(QWidget *parent) : QWidget(parent), ui(new Ui::TabularInput) {
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->widget->setVisible(ui->expandButton->isChecked());
    UTILITY_API->UpdateCloStyleForPlugIn(this);
}

TabularInput::~TabularInput() {
    delete ui;
}

QString TabularInput::getTitle() const {
    return ui->name->text();
}

void TabularInput::setTitle(const QString &title) const {
    ui->name->setText(title);
}