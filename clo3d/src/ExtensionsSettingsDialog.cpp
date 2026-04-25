#include "ExtensionsSettingsDialog.h"

#include <CLOAPIInterface.h>

#include "ui_ExtensionsSettingsDialog.h"

using namespace UI;

ExtensionsSettingsDialog::ExtensionsSettingsDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::ExtensionsSettingsDialog) {
    ui->setupUi(this);
    UTILITY_API->UpdateCloStyleForPlugIn(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setWindowModality(Qt::WindowModal);
}

ExtensionsSettingsDialog::~ExtensionsSettingsDialog() {
    delete ui;
}

void ExtensionsSettingsDialog::addPage(NamedWidget* page) const {
    ui->navigation->addPage(page);
}

void ExtensionsSettingsDialog::accept() {
    QDialog::accept();
}

void ExtensionsSettingsDialog::reject() {
    // QDialog::reject();
}
