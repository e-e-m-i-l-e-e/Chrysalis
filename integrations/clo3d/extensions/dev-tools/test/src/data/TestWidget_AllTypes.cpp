#include "data/TestWidget_AllTypes.h"
#include "ui_TestWidget_AllTypes.h"

TestWidget_AllTypes::TestWidget_AllTypes(QWidget* parent): QWidget(parent), ui(new Ui::TestWidget_AllTypes) {
    ui->setupUi(this);
}

TestWidget_AllTypes::~TestWidget_AllTypes()  {
    delete ui;
}
