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

void BaseExtensionsSettingsEditor::editSettings(const QString &groupName, const std::function<void(QSettings*)>& editor) const {
    settings_->beginGroup(groupName);
    editor(settings_);
    settings_->endGroup();
}
