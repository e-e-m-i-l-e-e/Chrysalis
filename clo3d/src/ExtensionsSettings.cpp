#include "ExtensionsSettings.h"

ExtensionsSettings::ExtensionsSettings(const QString &organization, const QString &application)
    : settings_(new QSettings(organization, application)) {}

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

void ExtensionsSettings::readSettings() const {
    for (const auto settings: extensionsSettings_) {
        settings->readSettings();
    }
}
