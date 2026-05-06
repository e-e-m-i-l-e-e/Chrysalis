#include "BaseExtensionSettingsWidget.h"

UI::BaseExtensionSettingsWidget::BaseExtensionSettingsWidget(BaseExtensionSettings* extensionSettings, QWidget *parent)
    :NamedWidget(parent), extensionSettings_(extensionSettings) {}

BaseExtensionSettings* UI::BaseExtensionSettingsWidget::getBaseExtensionSettings() const {
    return extensionSettings_;
}

void UI::BaseExtensionSettingsWidget::save() {
    extensionSettings_->writeSettings();
}

void UI::BaseExtensionSettingsWidget::read() {
    extensionSettings_->readSettings();
}
