#include "ExtensionsSettings.h"

ExtensionsSettings::ExtensionsSettings(const QString &organization, const QString &application)
    : BaseExtensionsSettingsEditor() {
    this->setSettings(new QSettings(organization, application));
}