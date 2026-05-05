#include "BaseExtensionsSettingsEditor.h"

BaseExtensionsSettingsEditor::BaseExtensionsSettingsEditor(const QString &organization, const QString &application) {
    settings_ = std::make_shared<QSettings>(organization, application);
}

void BaseExtensionsSettingsEditor::setSettings(const BaseExtensionsSettingsEditor* settingsEditor) {
    settings_ = settingsEditor->settings_;
}

Settings BaseExtensionsSettingsEditor::editSettings(const QString &groupName) const {
    return Settings(groupName, settings_);
}
