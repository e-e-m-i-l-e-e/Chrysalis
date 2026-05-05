#include "BaseExtensionsSettingsEditor.h"

#include <iostream>

void BaseExtensionsSettingsEditor::setSettings(QSettings* settings) {
    settings_ = settings;
}

Settings BaseExtensionsSettingsEditor::editSettings(const QString &groupName) const {
    for (const auto& key: settings_->allKeys()) {
        std::cout << key.toStdString() << " " << settings_->value(key).toString().toStdString() << std::endl;
    }
    return Settings(groupName, settings_);
}
