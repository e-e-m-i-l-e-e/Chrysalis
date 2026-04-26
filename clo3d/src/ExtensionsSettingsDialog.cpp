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

void ExtensionsSettingsDialog::addPage(BaseExtensionsSettingsPageWidget* page) const {
    ui->navigation->addPage(page);
}

void ExtensionsSettingsDialog::accept() {
    processPages([](BaseExtensionsSettingsPageWidget* extensionsSettingsPageWidget) {
        extensionsSettingsPageWidget->save();
    });
    QDialog::accept();
}

void ExtensionsSettingsDialog::reject() {
    processPages([](BaseExtensionsSettingsPageWidget* extensionsSettingsPageWidget) {
        extensionsSettingsPageWidget->reset();
    });
}

void ExtensionsSettingsDialog::processPages(void(*processor)(BaseExtensionsSettingsPageWidget*)) const {
    for (int i = 0; i < ui->navigation->count(); i++) {
        processor(qobject_cast<BaseExtensionsSettingsPageWidget*>(ui->navigation->getPage(i)));
    }
}
