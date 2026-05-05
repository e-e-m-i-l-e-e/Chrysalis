#include "XmlUIExporterOptions.h"

void XmlUIExporterOptions::read(const QSettings* settings) {
    BaseUIExporterOptions::read(settings);
    isEnabled_ = settings->value(Keys::IS_ENABLED, Defaults::IS_ENABLED).toBool();
    exportIcons_ = settings->value(Keys::EXPORT_ICONS, Defaults::EXPORT_ICONS).toBool();
    uiCompatible_ = settings->value(Keys::UI_COMPATIBLE, Defaults::UI_COMPATIBLE).toBool();
}

void XmlUIExporterOptions::write(QSettings* settings) {
    BaseUIExporterOptions::write(settings);
    settings->setValue(Keys::IS_ENABLED, isEnabled_);
    settings->setValue(Keys::EXPORT_ICONS, exportIcons_);
    settings->setValue(Keys::UI_COMPATIBLE, uiCompatible_);
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

void XmlUIExporterOptions::setIsEnabled(const bool isEnabled) {
    isEnabled_ = isEnabled;
}

void XmlUIExporterOptions::setExportIcons(const bool exportIcons) {
    exportIcons_ = exportIcons;
}

void XmlUIExporterOptions::setUICompatible(const bool uiCompatible) {
    uiCompatible_ = uiCompatible;
}