#include "ExtensionsSettingsDialog.h"
#include "ui_ExtensionsSettingsDialog.h"

#include <CLOAPIInterface.h>

#include "ExtensionsSettings.h"

using namespace UI;

ExtensionsSettingsDialog::ExtensionsSettingsDialog(ExtensionsSettings* settings, QWidget *parent)
    : QDialog(parent), ui(new Ui::ExtensionsSettingsDialog), extensionsSettings(settings) {
    ui->setupUi(this);
    UTILITY_API->UpdateCloStyleForPlugIn(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setWindowModality(Qt::WindowModal);
    connect(ui->reset, &QPushButton::clicked, this, &ExtensionsSettingsDialog::reset);
}

ExtensionsSettingsDialog::~ExtensionsSettingsDialog() {
    delete ui;
}

void ExtensionsSettingsDialog::addPage(BaseExtensionSettingsWidget* page) const {
    ui->navigation->addPage(page);
}

void ExtensionsSettingsDialog::accept() {
    processPages(&BaseExtensionSettingsWidget::write);
    QDialog::accept();
}

void ExtensionsSettingsDialog::reject() {
    processPages(&BaseExtensionSettingsWidget::read);
    QDialog::reject();
}

void ExtensionsSettingsDialog::reset() {
    extensionsSettings->clear();
    processPages(&BaseExtensionSettingsWidget::read);
}

int ExtensionsSettingsDialog::exec() {
    processPages(&BaseExtensionSettingsWidget::read);
    return QDialog::exec();
}

void ExtensionsSettingsDialog::processPages(void (BaseExtensionSettingsWidget::*processor)()) const {
    for (int i = 0; i < ui->navigation->count(); i++) {
        if (const auto extensionsSettingsPageWidget = qobject_cast<BaseExtensionSettingsWidget*>(ui->navigation->getPage(i))) {
            (extensionsSettingsPageWidget->*processor)();
        }
    }
}
