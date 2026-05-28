#include "BaseExtensionSettings.h"

#include "Logging.h"
#define LOGGER_NAME "Extensions Settings"

void BaseExtensionSettings::setSettings(QSettings *settings) {
    settings_ = settings;
}

void BaseExtensionSettings::readSettings() {
    const char* settingsName = typeid(*this).name() + 6;
    LOG_DEBUG("Reading \"{}\" settings", settingsName);
    settings_->beginGroup(settingsName);
    read();
    settings_->endGroup();
}

void BaseExtensionSettings::writeSettings() {
    const char* settingsName = typeid(*this).name() + 6;
    LOG_DEBUG("Writing \"{}\" settings", settingsName);
    settings_->beginGroup(settingsName);
    write();
    settings_->endGroup();
}
