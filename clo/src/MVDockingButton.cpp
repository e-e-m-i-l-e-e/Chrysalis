#include "MVDockingButton.h"
#include "ui_MVDockingButton.h"


MVDockingButton::MVDockingButton(QWidget *parent) : QWidget(parent), ui(new Ui::MVDockingButton) {
    ui->setupUi(this);
    ui->cloUICommon__Accordion->setAttribute(Qt::WA_StyledBackground, true);
}

MVDockingButton::~MVDockingButton() {
    delete ui;
}