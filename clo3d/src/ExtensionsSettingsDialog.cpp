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

void ExtensionsSettingsDialog::addPage(BaseExtensionsSettingsPageWidget* page) const {
    ui->navigation->addPage(page);
    page->getBaseExtensionsSettingsPage().setSettings(extensionsSettings);
}

void ExtensionsSettingsDialog::accept() {
    // Calls BaseExtensionsSettingsPageWidget::save
    processPages(&BaseExtensionsSettingsPageWidget::save);
    QDialog::accept();
}

void ExtensionsSettingsDialog::reject() {
    // Calls BaseExtensionsSettingsPageWidget::reset
    processPages(&BaseExtensionsSettingsPageWidget::reset);
}

int ExtensionsSettingsDialog::exec() {
    // Calls BaseExtensionsSettingsPageWidget::read
    processPages(&BaseExtensionsSettingsPageWidget::read);
    return QDialog::exec();
}

void ExtensionsSettingsDialog::processPages(void (BaseExtensionsSettingsPageWidget::*processor)()) const {
    for (int i = 0; i < ui->navigation->count(); i++) {
        if (const auto extensionsSettingsPageWidget = qobject_cast<BaseExtensionsSettingsPageWidget*>(ui->navigation->getPage(i))) {
            const auto _ = extensionsSettings->editSettings(extensionsSettingsPageWidget->getTitle());
            (extensionsSettingsPageWidget->*processor)();
        }
    }
}
