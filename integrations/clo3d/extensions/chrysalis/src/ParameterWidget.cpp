#include "ParameterWidget.h"
#include "ui_ParameterWidget.h"

using namespace UI;

ParameterWidget::ParameterWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::ParameterWidget) {
    ui->setupUi(this);
}

ParameterWidget::~ParameterWidget() {
    delete ui;
}

void ParameterWidget::setParameter(Chrysalis::Parameter* parameter) {
    parameter_ = parameter;
    ui->name->setText(parameter_->getName().data());
    if (parameter->hasValue()) ui->value->setText(QString::number(parameter_->getValue()));
    if (parameter->hasDefaultValue()) ui->value->setPlaceholderText(QString::number(parameter_->getDefaultValue()));
}
