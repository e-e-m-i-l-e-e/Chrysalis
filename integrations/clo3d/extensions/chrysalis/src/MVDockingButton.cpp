#include "MVDockingButton.h"
#include "ui_MVDockingButton.h"

using namespace CLO3D::UI;

MVDockingButton::MVDockingButton(QWidget *parent) : QWidget(parent), ui(new Ui::MVDockingButton) {
    ui->setupUi(this);
    ui->widget1->setAttribute(Qt::WA_StyledBackground, true);
}

MVDockingButton::~MVDockingButton() {
    delete ui;
}