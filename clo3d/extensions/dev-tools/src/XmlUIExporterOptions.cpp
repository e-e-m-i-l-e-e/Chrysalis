#include "XmlUIExporterOptions.h"

void XmlUIExporterOptions::read(const Settings &settings) {
    BaseUIExporterOptions::read(settings);
    isEnabled_ = settings.value(Keys::IS_ENABLED, Defaults::IS_ENABLED).toBool();
    exportIcons_ = settings.value(Keys::EXPORT_ICONS, Defaults::EXPORT_ICONS).toBool();
    uiCompatible_ = settings.value(Keys::UI_COMPATIBLE, Defaults::UI_COMPATIBLE).toBool();
}

bool XmlUIExporterOptions::getIsEnabled() const {
    return isEnabled_;
}

bool XmlUIExporterOptions::getExportIcons() const {
    return exportIcons_;
}

bool XmlUIExporterOptions::getUICompatible() const {
    return uiCompatible_;
}

void XmlUIExporterOptions::setIsEnabled(const Settings &settings, const bool isEnabled) {
    settings.setValue(Keys::IS_ENABLED, isEnabled);
    isEnabled_ = isEnabled;
}

void XmlUIExporterOptions::setExportIcons(const Settings &settings, const bool exportIcons) {
    settings.setValue(Keys::EXPORT_ICONS, exportIcons);
    exportIcons_ = exportIcons;
}

void XmlUIExporterOptions::setUICompatible(const Settings &settings, const bool uiCompatible) {
    settings.setValue(Keys::UI_COMPATIBLE, uiCompatible);
    uiCompatible_ = uiCompatible;
}