#include "BaseExtensionsSettingsEditor.h"

BaseExtensionsSettingsEditor::~BaseExtensionsSettingsEditor() {
    delete settings_;
}

void BaseExtensionsSettingsEditor::setSettings(QSettings* settings) {
    settings_ = settings;
}

void BaseExtensionsSettingsEditor::setSettings(std::shared_ptr<BaseExtensionsSettingsEditor> settingsEditor) {
    settings_ = settingsEditor->settings_;
}

Settings BaseExtensionsSettingsEditor::editSettings(const QString &groupName) const {
    return Settings(groupName, settings_);
}
