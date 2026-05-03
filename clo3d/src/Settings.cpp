#include "Settings.h"

Settings::Settings(const QString &groupName, QSettings *settings): settings_(settings) {
    settings_->beginGroup(groupName);
}

Settings::~Settings() {
    settings_->endGroup();
}

void Settings::setValue(const QString &key, const QVariant &value) const {
    settings_->setValue(key, value);
}

QVariant Settings::value(const QString &key, const QVariant &defaultValue) const {
    return settings_->value(key, defaultValue);
}
