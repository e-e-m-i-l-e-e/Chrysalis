#include "ExtensionsSettings.h"

ExtensionsSettings::ExtensionsSettings(const QString &organization, const QString &application)
    : BaseExtensionsSettingsEditor(organization, application) {}

ExtensionsSettings::~ExtensionsSettings() {
    for (const auto settings: settings_) {
        delete settings;
    }
}

void ExtensionsSettings::addSettings(BaseExtensionsSettingsPage* settings) {
    settings_.push_front(settings);
    settings->setSettings(this);
}

void ExtensionsSettings::readSettings() const {
    for (const auto settings: settings_) {
        settings->readSettings();
    }
}
