#include "DialogPreference.h"
#include "ui_DialogPreference.h"

DialogPreference::DialogPreference(QWidget *parent) : MVDialog(parent), ui(new Ui::DialogPreference) {
    ui->setupUi(this);
    UTILITY_API->UpdateCloStyleForPlugIn(this);

    connect(ui->listWidget, &QListWidget::currentRowChanged,
            ui->stackedWidget, &QStackedWidget::setCurrentIndex);

    connect(ui->pushButton15, &QPushButton::clicked, this, &QDialog::accept);
}

DialogPreference::~DialogPreference() {
    delete ui;
}