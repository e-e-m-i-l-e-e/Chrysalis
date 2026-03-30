#include "MVDockingButton.h"
#include "ui_MVDockingButton.h"


MVDockingButton::MVDockingButton(QWidget *parent) : QWidget(parent), ui(new Ui::MVDockingButton) {
    ui->setupUi(this);
}

MVDockingButton::~MVDockingButton() {
    delete ui;
}