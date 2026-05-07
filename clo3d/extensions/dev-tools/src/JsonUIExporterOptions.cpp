#include "JsonUIExporterOptions.h"

bool JsonUIExporterOptions::isEnabled() {
    return isEnabled_;
}

void JsonUIExporterOptions::read(const QSettings* settings) {
    BaseUIExporterOptions::read(settings);
    isEnabled_ = settings->value(Keys::IS_ENABLED, Defaults::IS_ENABLED).toBool();
    ignoreCSS_ = settings->value(Keys::IGNORE_CSS, Defaults::IGNORE_CSS).toBool();
    visibleOnly_ = settings->value(Keys::VISIBLE_ONLY, Defaults::VISIBLE_ONLY).toBool();
}

void JsonUIExporterOptions::write(QSettings* settings) {
    BaseUIExporterOptions::write(settings);
    settings->setValue(Keys::IS_ENABLED, isEnabled_);
    settings->setValue(Keys::IGNORE_CSS, ignoreCSS_);
    settings->setValue(Keys::VISIBLE_ONLY, visibleOnly_);
}

bool JsonUIExporterOptions::getIgnoreCSS() const {
    return ignoreCSS_;
}

bool JsonUIExporterOptions::getVisibleOnly() const {
    return visibleOnly_;
}

void JsonUIExporterOptions::setIsEnabled(const bool isEnabled) {
    isEnabled_ = isEnabled;
}

void JsonUIExporterOptions::setIgnoreCSS(const bool ignoreCSS) {
    ignoreCSS_ = ignoreCSS;
}

void JsonUIExporterOptions::setVisibleOnly(const bool visibleOnly) {
    visibleOnly_ = visibleOnly;
}