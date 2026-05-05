#include "ExtensionsSettingsDialog.h"

#include <CLOAPIInterface.h>

#include "ExtensionsSettings.h"
#include "ui_ExtensionsSettingsDialog.h"

using namespace UI;

ExtensionsSettingsDialog::ExtensionsSettingsDialog(ExtensionsSettings* settings, QWidget *parent)
    : QDialog(parent), ui(new Ui::ExtensionsSettingsDialog), extensionsSettings(settings) {
    ui->setupUi(this);
    UTILITY_API->UpdateCloStyleForPlugIn(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setWindowModality(Qt::WindowModal);
}

ExtensionsSettingsDialog::~ExtensionsSettingsDialog() {
    delete ui;
}

void ExtensionsSettingsDialog::addPage(BaseExtensionSettingsWidget* page) const {
    ui->navigation->addPage(page);
}

void ExtensionsSettingsDialog::accept() {
    // Calls BaseExtensionSettingsWidget::save
    processPages(&BaseExtensionSettingsWidget::save);
    QDialog::accept();
}

void ExtensionsSettingsDialog::reject() {
    // Calls BaseExtensionSettingsWidget::reset
    processPages(&BaseExtensionSettingsWidget::reset);
}

int ExtensionsSettingsDialog::exec() {
    // Calls BaseExtensionSettingsWidget::read
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
