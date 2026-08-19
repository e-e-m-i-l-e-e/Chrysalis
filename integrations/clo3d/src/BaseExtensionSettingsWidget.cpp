#include "BaseExtensionSettingsWidget.h"

using namespace CLO3D::UI;

BaseExtensionSettingsWidget::BaseExtensionSettingsWidget(BaseExtensionSettings* extensionSettings, QWidget *parent)
    :NamedWidget(parent), extensionSettings_(extensionSettings) {}

CLO3D::BaseExtensionSettings* BaseExtensionSettingsWidget::getBaseExtensionSettings() const {
    return extensionSettings_;
}

void BaseExtensionSettingsWidget::write() {
    extensionSettings_->writeSettings();
}

void BaseExtensionSettingsWidget::read() {
    extensionSettings_->readSettings();
}
