#include "XmlUIExporterOptions.h"

XmlUIExporterOptions::XmlUIExporterOptions(const QSettings* settings)
    : BaseUIExporterOptions(settings) {}

bool XmlUIExporterOptions::getExportIcons() const {
    return true;
}

bool XmlUIExporterOptions::getUICompatible() const {
    return true;
}
