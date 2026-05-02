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
    processPages([this](BaseExtensionsSettingsPageWidget* extensionsSettingsPageWidget) {
        extensionsSettings->editSettings(extensionsSettingsPageWidget->getTitle(), [extensionsSettingsPageWidget](QSettings*) {
            extensionsSettingsPageWidget->save();
        });
    });
    QDialog::accept();
}

void ExtensionsSettingsDialog::reject() {
    processPages([](BaseExtensionsSettingsPageWidget* extensionsSettingsPageWidget) {
        extensionsSettingsPageWidget->reset();
    });
}

int ExtensionsSettingsDialog::exec() {
    processPages([this](BaseExtensionsSettingsPageWidget* extensionsSettingsPageWidget) {
        extensionsSettings->editSettings(extensionsSettingsPageWidget->getTitle(), [extensionsSettingsPageWidget](QSettings*) {
            extensionsSettingsPageWidget->read();
        });
    });
    return QDialog::exec();
}

void ExtensionsSettingsDialog::processPages(const std::function<void(BaseExtensionsSettingsPageWidget*)> &processor) const {
    for (int i = 0; i < ui->navigation->count(); i++) {
        processor(qobject_cast<BaseExtensionsSettingsPageWidget*>(ui->navigation->getPage(i)));
    }
}
