#include "BaseExtensionsSettingsEditor.h"

#include <iostream>

BaseExtensionsSettingsEditor::BaseExtensionsSettingsEditor(const QString &organization, const QString &application) {
    std::cout << organization.toStdString() << " " << application.toStdString() << std::endl;
    settings_ = std::make_shared<QSettings>(organization, application);
}

void BaseExtensionsSettingsEditor::setSettings(const BaseExtensionsSettingsEditor* settingsEditor) {
    settings_ = settingsEditor->settings_;
}

Settings BaseExtensionsSettingsEditor::editSettings(const QString &groupName) const {
    for (const auto key: settings_->allKeys()) {
        std::cout << key.toStdString() << " " << settings_->value(key).toString().toStdString() << std::endl;
    }
    return Settings(groupName, settings_);
}
