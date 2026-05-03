#include "ExtensionsSettingsDialog.h"

#include <CLOAPIInterface.h>

#include "ExtensionsSettings.h"
#include "ui_ExtensionsSettingsDialog.h"

using namespace UI;

ExtensionsSettingsDialog::ExtensionsSettingsDialog(const std::shared_ptr<ExtensionsSettings> &settings, QWidget *parent)
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
    processPages([](auto* w) { w->save(); });
    QDialog::accept();
}

void ExtensionsSettingsDialog::reject() {
    processPages(&BaseExtensionsSettingsPageWidget::reset);
}

int ExtensionsSettingsDialog::exec() {
    processPages([](auto* w) { w->read(); });
    return QDialog::exec();
}
