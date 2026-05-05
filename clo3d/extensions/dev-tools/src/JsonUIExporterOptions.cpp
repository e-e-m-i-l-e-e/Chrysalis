#include "JsonUIExporterOptions.h"

void JsonUIExporterOptions::read(const Settings &settings) {
    BaseUIExporterOptions::read(settings);
    isEnabled_ = settings.value(Keys::IS_ENABLED, Defaults::IS_ENABLED).toBool();
    ignoreCSS_ = settings.value(Keys::IGNORE_CSS, Defaults::IGNORE_CSS).toBool();
    visibleOnly_ = settings.value(Keys::VISIBLE_ONLY, Defaults::VISIBLE_ONLY).toBool();
}

bool JsonUIExporterOptions::getIsEnabled() const {
    return isEnabled_;
}

bool JsonUIExporterOptions::getIgnoreCSS() const {
    return ignoreCSS_;
}

bool JsonUIExporterOptions::getVisibleOnly() const {
    return visibleOnly_;
}

void JsonUIExporterOptions::setIsEnabled(const Settings &settings, const bool isEnabled) {
    settings.setValue(Keys::IS_ENABLED, isEnabled_);
    isEnabled_ = isEnabled;
}

void JsonUIExporterOptions::setIgnoreCSS(const Settings &settings, const bool ignoreCSS) {
    settings.setValue(Keys::IGNORE_CSS, ignoreCSS_);
    ignoreCSS_ = ignoreCSS;
}

void JsonUIExporterOptions::setVisibleOnly(const Settings &settings, const bool visibleOnly) {
    settings.setValue(Keys::VISIBLE_ONLY, visibleOnly_);
    visibleOnly_ = visibleOnly;
}