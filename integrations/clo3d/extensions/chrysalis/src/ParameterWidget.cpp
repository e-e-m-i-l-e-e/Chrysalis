#include "ParameterWidget.h"

#include <iostream>

#include "ui_ParameterWidget.h"

#include <QDoubleValidator>

using namespace UI;

ParameterWidget::ParameterWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::ParameterWidget) {
    ui->setupUi(this);
    ui->value->setValidator(new QDoubleValidator(ui->value));
    connect(ui->value, &QLineEdit::textChanged, [this](const QString& text) {
        parameter_->setValue(text.toDouble());
    });
}

ParameterWidget::~ParameterWidget() {
    delete ui;
}

void ParameterWidget::set(Chrysalis::Parameter* parameter) {
    parameter_ = parameter;
    ui->name->setText(parameter_->getName().data());
    if (parameter->hasValue()) ui->value->setText(QString::number(parameter_->getValue()));
    if (parameter->hasDefaultValue()) ui->value->setPlaceholderText(QString::number(parameter_->getDefaultValue()));
}
