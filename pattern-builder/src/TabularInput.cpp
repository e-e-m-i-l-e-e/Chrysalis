//
// Created by emily on 03/04/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_TabularInput.h" resolved

#include "TabularInput.h"
#include "ui_TabularInput.h"


TabularInput::TabularInput(QWidget *parent) : QWidget(parent), ui(new Ui::TabularInput) {
    ui->setupUi(this);
}

TabularInput::~TabularInput() {
    delete ui;
}