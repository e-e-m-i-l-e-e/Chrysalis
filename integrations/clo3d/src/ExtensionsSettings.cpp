#include "ExtensionsSettings.h"

#include "Logging.h"
#define LOGGER_NAME "Extensions Settings"

ExtensionsSettings::ExtensionsSettings(QSettings* settings): settings_(settings) {}

ExtensionsSettings::~ExtensionsSettings() {
    for (const auto settings: extensionsSettings_) {
        delete settings;
    }
    delete settings_;
}

void ExtensionsSettings::addSettings(BaseExtensionSettings* settings) {
    extensionsSettings_.push_front(settings);
    settings->setSettings(settings_);
}

void ExtensionsSettings::read() const {
    for (const auto settings: extensionsSettings_) {
        settings->readSettings();
    }
}

void ExtensionsSettings::clear() const {
    LOG_INFO("Resetting settings");
    settings_->clear();
    read();
}
